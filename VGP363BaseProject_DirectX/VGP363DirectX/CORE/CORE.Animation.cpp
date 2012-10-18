// CORE.Animation.cpp
/////////////////////////////////////////////////////////

#include "..\GameCore.h"
#include <math.h>

namespace GameCore {
	
	double Linear(double fPercent) {
		return fPercent;
	}

	double EaseIn(double fPercent) {
		return fPercent * fPercent;
	}

	double EaseOut(double fPercent) {
		return (1.0 - fPercent)*(fPercent - 1.0) + 1.0;
	}

	double EaseInOut(double fPercent) {
		double e = 2.718281828;
		return 1.0 / (1.0 + (double)pow(e, -10.0*(double)fPercent + 5.0));
	}

	Animation::Animation() {
		this->m_pReference = NULL;
		this->m_pValue = NULL;
		this->m_fValFrom = 0.0;
		this->m_fValTo = 0.0;
		this->m_pInterpFunc = NULL;
		this->m_pCompletedEvent = NULL;
		this->m_fTimeStart = 0.0;
		this->m_fTimeEnd = 0.0;
		this->m_bActive = false;
		this->m_bCompleted = false;
		this->m_nAnimationMode = ANIM_NORMAL;
	}

	double __Interpolate_(
		double fStartValue, double fEndValue,
		double fStartTime, double fCurrentTime, double fEndTime,
		InterpFunc pInterpFunc
	){
		if(pInterpFunc == NULL) return fEndValue;
		if(fCurrentTime >= fEndTime) return fEndValue;
		if(fEndTime <= fStartTime) return fEndValue;
		if(fCurrentTime <= fStartTime) return fStartValue;
		double fPercent = (fCurrentTime-fStartTime)/(fEndTime-fStartTime);
		return fStartValue + pInterpFunc(fPercent)*(fEndValue-fStartValue);
	}

	void Animation::_RunAnimation(double fCurrentTime) {
		if(this->m_pValue == NULL) return;
		if(this->m_bActive == false) return;
		if(this->m_bCompleted == true) return;
		*this->m_pValue = __Interpolate_(
			this->m_fValFrom, this->m_fValTo,
			this->m_fTimeStart, fCurrentTime, this->m_fTimeEnd,
			this->m_pInterpFunc
		);
		if(*this->m_pValue == this->m_fValTo) {
			if(this->m_nAnimationMode == ANIM_OSCILLATE) {
				double fTemp = this->m_fValFrom;
				this->m_fValFrom = this->m_fValTo;
				this->m_fValTo = fTemp;
				this->m_fTimeEnd = fCurrentTime + (this->m_fTimeEnd - this->m_fTimeStart);
				this->m_fTimeStart = fCurrentTime;
			} else if(this->m_nAnimationMode == ANIM_REPEAT) { 
				this->m_fTimeEnd = fCurrentTime + (this->m_fTimeEnd - this->m_fTimeStart);
				this->m_fTimeStart = fCurrentTime;			
			} else {
				this->m_bCompleted = true;
				if(this->m_pCompletedEvent != NULL) {
					this->m_pCompletedEvent(this);
				}
			}
		}
	}

	AnimationSystem::AnimationSystem() {
		// Nothing to initialize
	}

	Animation* AnimationSystem::_NewAnimation(double *pdouble, InterpFunc pInterpFunc, double fStartValue, double fEndValue, double fCurrentTime, double fStartTime, double fEndTime) {
		Animation *pAnimation = new Animation();
		///////////////////////////////////////////////////////////////
		// 0.0 as the start time indicates it will start immediately //
		if(fStartTime == 0.0) {
			fStartTime = fCurrentTime;
			fEndTime = fCurrentTime + fEndTime;
		}
		///////////////////////////////////////////////////////////////
		pAnimation->m_pReference = NULL;
		pAnimation->m_pValue = pdouble;
		pAnimation->m_fValFrom = fStartValue;
		pAnimation->m_fValTo = fEndValue;
		pAnimation->m_pInterpFunc = pInterpFunc;
		pAnimation->m_fTimeStart = fStartTime;
		pAnimation->m_fTimeEnd = fEndTime;
		pAnimation->m_bActive = true;
		this->m_Animations._Add(pAnimation);
		return pAnimation;
	}

	void AnimationSystem::_RunAnimations(double fCurrentTime) {
		this->m_Animations._BeginEnumerate();
		Animation* pAnim = this->m_Animations._GetNextData();
		while(pAnim != NULL) {
			pAnim->_RunAnimation(fCurrentTime);
			pAnim = this->m_Animations._GetNextData();
		}
	}

	void AnimationSystem::_ClearAll() {
		this->m_Animations._DeleteAll();
	}

}