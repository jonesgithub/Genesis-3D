/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU

http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "stdneb.h"
#include "particles/affectors/particleTextureRotatorAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_UseOwnRotationSpeed = "UseOwnRotationSpeed";
	const static char* s_Rotation = "Rotation";
	const static char* s_RotationSpeed = "RotationSpeed";
	const static char* s_RandomRotationSpeed = "RandomRotationSpeed";

	const static char* s_IsRotateByLifeTime = "RotateByLifeTime";
	const static char* s_StartAngle = "StartAngle";
	const static char* s_EndAngle = "EndAngle";
	const static char*	s_Random = "Random";

	extern const char*	s_KeyFrameCount;
	extern const char*	s_CurveKey;
	extern const char*	s_CurveValue;

	class TextureRotatorAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( TextureRotatorAffector* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if( 2 == ver)
			{
				Load_2(obj, pReader);
				return;
			}
			else if(3 == ver)
			{
				Load_3(obj, pReader);
				return;
			}
			else if( 4 == ver)
			{
				Load_4(obj,pReader);
				return;
			}
			else if( 5 == ver)
			{
				Load_5(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(TextureRotatorAffector* obj, SerializeReader* pReader)
		{

		}
		//------------------------------------------------------------------------
		void Load_2(TextureRotatorAffector* obj, SerializeReader* pReader)
		{
		}
		//--------------------------------------------------------------------------------
		void Load_3(TextureRotatorAffector* obj, SerializeReader* pReader)
		{
			bool mIsRandomRotate;
			pReader->SerializeBool(s_Random, mIsRandomRotate );

			if(mIsRandomRotate)
			{
				obj->getMinMaxCurve(Affector_RotationAngular)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_RotationAngular)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;		
			Util::Array<Math::float2> keyframelist2;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_RotationAngular);
			_serializeLoadCurveOld(pReader, keyframelist1, "minAngular", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, "maxAngular", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//--------------------------------------------------------------------------------
		void Load_4(TextureRotatorAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_RotationAngular),"Angular",s_CurveKey);
		}
		//--------------------------------------------------------------------------------
		void Load_5(TextureRotatorAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_RotationAngular),"Angular",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const TextureRotatorAffector* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((TextureRotatorAffector* )obj)->getMinMaxCurve(Affector_RotationAngular),"Angular",s_CurveKey);		
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion TextureRotatorAffector::GetVersion() const
	{
		return 5;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void TextureRotatorAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		TextureRotatorAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void TextureRotatorAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		TextureRotatorAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void TextureRotatorAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<TextureRotatorAffector> source = target.downcast<TextureRotatorAffector>();

		_serializeCopyMinMaxCurve(source->mMinMaxRotation,this->mMinMaxRotation);

	}

}