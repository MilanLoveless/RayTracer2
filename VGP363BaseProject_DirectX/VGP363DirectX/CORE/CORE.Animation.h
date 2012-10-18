// CORE.Animation.h
/////////////////////////////////////////////////////////

#ifndef __CORE_ANIMATION_H_
#define __CORE_ANIMATION_H_

#include "CORE.Collection.h"

namespace GameCore {

	class Animation;

	typedef double (*InterpFunc)(double fPercent); 
	typedef void (*CompletedFunc)(Animation *pSender);

	double Linear(double fPercent);
	double EaseIn(double fPercent);
	double EaseOut(double fPercent);
	double EaseInOut(double fPercent);

	enum ANIMATION_MODE { ANIM_NORMAL=0, ANIM_REPEAT=1, ANIM_OSCILLATE=2 };

	class Animation {
	public:
		Animation();

		void* m_pReference;
		double* m_pValue;

		double m_fValFrom;
		double m_fValTo;
		InterpFunc m_pInterpFunc;
		CompletedFunc m_pCompletedEvent;
		double m_fTimeStart;
		double m_fTimeEnd;

		void _RunAnimation(double fCurrentTime);

		bool m_bActive;
		bool m_bCompleted;
		ANIMATION_MODE m_nAnimationMode;
	};

	class AnimationSystem {
		Collection<Animation> m_Animations;
	public:
		AnimationSystem();

		Animation* _NewAnimation(double *pdouble, InterpFunc pInterpFunc, double fStartValue, double fEndValue, double fCurrentime, double fStartTime, double fEndTime);
		void _RunAnimations(double fCurrentTime);
		void _ClearAll();
	};

}

#endif