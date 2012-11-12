// Sampler.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sampler.h"

namespace ThreeD
{
	_SAMPLER::_SAMPLER()
	{
		_SeedRand;
		num_samples = 1;
		num_sets = 83;
		count = 0;
		jump = 0;
		samples.reserve(num_samples * num_sets);
		_SetupShuffledIndices();
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_SAMPLER::_SAMPLER(const int ns)
	{
		num_samples = ns;
		num_sets = 83;
		count = 0;
		jump = 0;
		samples.reserve(num_samples * num_sets);
		_SetupShuffledIndices();
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_SAMPLER::_SAMPLER(const int ns, const int n_sets)
	{
		num_samples = ns;
		num_sets = n_sets;
		count = 0;
		jump = 0;
		samples.reserve(num_samples * num_sets);
		_SetupShuffledIndices();
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_SAMPLER::_SAMPLER(const _SAMPLER &s)
	{
		num_samples = s.num_samples;
		num_sets = s.num_sets;
		samples = s.samples;
		shuffled_indices = s.shuffled_indices;
		disk_samples = s.disk_samples;
		hemisphere_samples = s.hemisphere_samples;
		sphere_samples = s.sphere_samples;
		count = s.count;
		jump = s.jump;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_SAMPLER& _SAMPLER::operator= (const _SAMPLER &s)
	{
		if (this == &s)
			return (*this);

		num_samples = s.num_samples;
		num_sets = s.num_sets;
		samples = s.samples;
		shuffled_indices = s.shuffled_indices;
		disk_samples = s.disk_samples;
		hemisphere_samples = s.hemisphere_samples;
		sphere_samples = s.sphere_samples;
		count = s.count;
		jump = s.jump;
		
		return (*this);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_SAMPLER::~_SAMPLER() {}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_SetNumSets(const int ns)
	{
		num_sets = ns;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_SetNumSamples(const int ns)
	{
		num_samples = ns;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_ShuffleXCoords()
	{
		for(int p=0; p < num_sets; p++)
		{
			for(int i = 0; i < num_samples - 1; i ++)
			{
				int target = _RandInt % num_samples + p * num_samples;
				_DOUBLE temp = samples[i + p * num_samples + 1].x;
				samples[i + p * num_samples + 1].x = samples[target].x;
				samples[target].x = temp;
			}
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_ShuffleYCoords()
	{
		for(int p=0; p < num_sets; p++)
		{
			for(int i = 0; i < num_samples - 1; i ++)
			{
				int target = _RandInt % num_samples + p * num_samples;
				_DOUBLE temp = samples[i + p * num_samples + 1].y;
				samples[i + p * num_samples + 1].y = samples[target].y;
				samples[target].y = temp;
			}
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_SetupShuffledIndices()
	{
		shuffled_indices.reserve(num_samples * num_sets);
		vector<int> indices;

		for(int j = 0; j < num_samples; j++)
		{
			indices.push_back(j);
		}

		for(int i = 0; i < num_sets; i++)
		{
			random_shuffle(indices.begin(), indices.end());
			for(int p = 0; p < num_samples; p++)
			{
				shuffled_indices.push_back(indices[p]);
			}
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_MapToDisk()
	{
		int size = samples.size();
		_DOUBLE r, phi;
		_POINT2D sp;

		disk_samples.reserve(size);

		for(int j = 0; j < size; j++)
		{
			sp.x = 2.0 * samples[j].x - 1.0;
			sp.y = 2.0 * samples[j].y - 1.0;
			if (sp.x > -sp.y)
			{
				if (sp.x > sp.y)
				{
					r = sp.x;
					phi = sp.y / sp.x;
				}
				else
				{
					r = sp.y;
					phi = 2 - sp.x / sp.y;
				}
			}
			else {
				if (sp.x < sp.y) {
					r = -sp.x;
					phi = 4 + sp.y / sp.x;
				}
				else {
					r = -sp.y;
					if (sp.y != 0.0)
						phi = 6 - sp.x / sp.y;
					else
						phi  = 0.0;
				}
			}
		
			phi *= PI / 4.0;
				
			disk_samples[j].x = r * cos(phi);
			disk_samples[j].y = r * sin(phi);
		}
	
		samples.erase(samples.begin(), samples.end());
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_MapToHemisphere(const _DOUBLE exp)
	{
		int size = samples.size();
		hemisphere_samples.reserve(num_samples * num_sets);
		
		for (int j = 0; j < size; j++)
		{
			_DOUBLE cos_phi = cos(2.0 * PI * samples[j].x);
			_DOUBLE sin_phi = sin(2.0 * PI * samples[j].x);	
			_DOUBLE cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
			_DOUBLE sin_theta = sqrt (1.0 - cos_theta * cos_theta);
			_DOUBLE px = sin_theta * cos_phi;
			_DOUBLE py = sin_theta * sin_phi;
			_DOUBLE pz = cos_theta;
			hemisphere_samples.push_back(_VERTEX4F(px, py, pz, 1.0));
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void _SAMPLER::_MapToSphere()
	{
		_DOUBLE r1, r2;
		_DOUBLE x, y, z;
		_DOUBLE r, phi;

			sphere_samples.reserve(num_samples * num_sets);   
		
		for (int j = 0; j < num_samples * num_sets; j++)
		{
			r1 	= samples[j].x;
    		r2 	= samples[j].y;
    		z 	= 1.0 - 2.0 * r1;
    		r 	= sqrt(1.0 - z * z);
    		phi = TWO_PI * r2;
    		x 	= r * cos(phi);
    		y 	= r * sin(phi);
			sphere_samples.push_back(_VERTEX4F(x, y, z, 1.0)); 
		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_POINT2D _SAMPLER::_SampleSquare()
	{
		if(count % num_samples == 0)
		{
			jump = (_RandInt % num_sets) * num_samples;
		}
		return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_POINT2D _SAMPLER::_SampleDisk()
	{
		if (count % num_samples == 0)  									// start of a new pixel
		jump = (_RandInt % num_sets) * num_samples;
	
		return (disk_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_VERTEX4F _SAMPLER::_SampleHemisphere()
	{
		if(count % num_samples == 0)
		{
			jump = (_RandInt % num_sets) * num_samples;
		}

		return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_VERTEX4F _SAMPLER::_SampleSphere()
	{
		if (count % num_samples == 0)
			jump = (_RandInt % num_sets) * num_samples;
		
		return (sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int _SAMPLER::_GetNumSamples()
	{
		return num_samples;
	}
}