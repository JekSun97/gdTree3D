/*
proctree.js Copyright (c) 2012, Paul Brunt
c++ port Copyright (c) 2015, Jari Komppa
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
* Neither the name of proctree.js nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL PAUL BRUNT BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cmath>
#include <string.h>
#include "proctree.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795f
#endif

namespace Proctree
{
	float length(fvec3 a)
	{
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	fvec3 normalize(fvec3 a)
	{
		float l = length(a);
		if (l != 0)
		{
			l = 1.0f / l;
			a.x *= l;
			a.y *= l;
			a.z *= l;
		}
		return a;
	}

	fvec3 cross(fvec3 a, fvec3 b)
	{
		fvec3 c =
		{
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
		return c;
	}

	float dot(fvec3 a, fvec3 b)
	{
		return a.x * b.x +
			   a.y * b.y +
			   a.z * b.z;
	}

	fvec3 sub(fvec3 a, fvec3 b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		return a;
	}

	fvec3 add(fvec3 a, fvec3 b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		return a;
	}

	fvec3 scaleVec(fvec3 a, float b)
	{
		a.x *= b;
		a.y *= b;
		a.z *= b;
		return a;
	}

	fvec3 scaleInDirection(fvec3 aVector, fvec3 aDirection, float aScale)
	{
		float currentMag = dot(aVector, aDirection);

		fvec3 change = scaleVec(aDirection, currentMag * aScale - currentMag);
		return add(aVector, change);
	}

	fvec3 vecAxisAngle(fvec3 aVec, fvec3 aAxis, float aAngle)
	{
		//v std::cos(T) + (axis x v) * std::sin(T) + axis*(axis . v)(1-std::cos(T)
		float cosr = std::cos(aAngle);
		float sinr = std::sin(aAngle);
		return add(add(scaleVec(aVec, cosr), scaleVec(cross(aAxis, aVec), sinr)), 
			           scaleVec(aAxis, dot(aAxis, aVec) * (1 - cosr)));
	}

	fvec3 mirrorBranch(fvec3 aVec, fvec3 aNorm, Properties &aProperties)
	{
		fvec3 v = cross(aNorm, cross(aVec, aNorm));
		float s = aProperties.mBranchFactor * dot(v, aVec);
		fvec3 res = {
			aVec.x - v.x * s,
			aVec.y - v.y * s,
			aVec.z - v.z * s
		};
		return res;
	}

	Properties::Properties(
		float aClumpMax,
		float aClumpMin,
		float aLengthFalloffFactor,
		float aLengthFalloffPower,
		float aBranchFactor,
		float aRadiusFalloffRate,
		float aClimbRate,
		float aTrunkKink,
		float aMaxRadius,
		int aTreeSteps,
		float aTaperRate,
		float aTwistRate,
		int aSegments,
		int aLevels,
		float aSweepAmount,
		float aInitialBranchLength,
		float aTrunkLength,
		float aDropAmount,
		float aGrowAmount,
		float aVMultiplier,
		float aTwigScale,
		int aSeed)
	{
		mSeed = aSeed;
		mSegments = aSegments;
		mLevels = aLevels;
		mVMultiplier = aVMultiplier;
		mTwigScale = aTwigScale;
		mInitialBranchLength = aInitialBranchLength;
		mLengthFalloffFactor = aLengthFalloffFactor;
		mLengthFalloffPower = aLengthFalloffPower;
		mClumpMax = aClumpMax;
		mClumpMin = aClumpMin;
		mBranchFactor = aBranchFactor;
		mDropAmount = aDropAmount;
		mGrowAmount = aGrowAmount;
		mSweepAmount = aSweepAmount;
		mMaxRadius = aMaxRadius;
		mClimbRate = aClimbRate;
		mTrunkKink = aTrunkKink;
		mTreeSteps = aTreeSteps;
		mTaperRate = aTaperRate;
		mRadiusFalloffRate = aRadiusFalloffRate;
		mTwistRate = aTwistRate;
		mTrunkLength = aTrunkLength;
	}

	Properties::Properties()
	{
		mSeed = 262;
		mSegments = 6;
		mLevels = 5;
		mVMultiplier = 0.36f;
		mTwigScale = 0.39f;
		mInitialBranchLength = 0.49f;
		mLengthFalloffFactor = 0.85f;
		mLengthFalloffPower = 0.99f;
		mClumpMax = 0.454f;
		mClumpMin = 0.404f;
		mBranchFactor = 2.45f;
		mDropAmount = -0.1f;
		mGrowAmount = 0.235f;
		mSweepAmount = 0.01f;
		mMaxRadius = 0.139f;
		mClimbRate = 0.371f;
		mTrunkKink = 0.093f;
		mTreeSteps = 5;
		mTaperRate = 0.947f;
		mRadiusFalloffRate = 0.73f;
		mTwistRate = 3.02f;
		mTrunkLength = 2.4f;
	}

	float Properties::random(float aFixed)
	{
		if (!aFixed)
		{
			aFixed = (float)mRseed++;
		}
		return std::abs(std::cos(aFixed + aFixed * aFixed));
	}


	Branch::~Branch()
	{
		delete mChild0;
		delete mChild1;
		delete[] mRootRing;
		delete[] mRing0;
		delete[] mRing1;
		delete[] mRing2;
	}

	Branch::Branch()
	{
		mRootRing = 0;
		mRing0 = 0;
		mRing1 = 0;
		mRing2 = 0;
		mChild0 = 0;
		mChild1 = 0;
		mParent = 0;
		mLength = 1;
		mTrunktype = 0;
		mRadius = 0;
		mHead = { 0, 0, 0 };
		mTangent = { 0, 0, 0 };
		mEnd = 0;
	}

	Branch::Branch(fvec3 aHead, Branch *aParent)
	{
		mRootRing = 0;
		mRing0 = 0;
		mRing1 = 0;
		mRing2 = 0;
		mChild0 = 0;
		mChild1 = 0;
		mLength = 1;
		mTrunktype = 0;
		mRadius = 0;
		mHead = aHead;
		mTangent = { 0, 0, 0 };
		mParent = aParent;
		mEnd = 0;
	}

	void Branch::split(int aLevel, int aSteps, Properties &aProperties, int aL1/* = 1*/, int aL2/* = 1*/)
	{
		int rLevel = aProperties.mLevels - aLevel;
		fvec3 po;
		if (this->mParent)
		{
			po = mParent->mHead;
		}
		else
		{
			po = { 0, 0, 0 };
			mTrunktype = 1;
		}
		fvec3 so = mHead;
		fvec3 dir = normalize(sub(so, po));

		fvec3 a = { dir.z, dir.x, dir.y };
		fvec3 normal = cross(dir, a);
		fvec3 tangent = cross(dir, normal);
		float r = aProperties.random(rLevel * 10 + aL1 * 5.0f + aL2 + aProperties.mSeed);
		//float r2 = aProperties.random(rLevel * 10 + aL1 * 5.0f + aL2 + 1 + aProperties.seed); // never used

		fvec3 adj = add(scaleVec(normal, r), scaleVec(tangent, 1 - r));
		if (r > 0.5) adj = scaleVec(adj, -1);

		float clump = (aProperties.mClumpMax - aProperties.mClumpMin) * r + aProperties.mClumpMin;
		fvec3 newdir = normalize(add(scaleVec(adj, 1 - clump), scaleVec(dir, clump)));


		fvec3 newdir2 = mirrorBranch(newdir, dir, aProperties);
		if (r > 0.5)
		{
			fvec3 tmp = newdir;
			newdir = newdir2;
			newdir2 = tmp;
		}

		if (aSteps > 0)
		{
			float angle = aSteps / (float)aProperties.mTreeSteps * 2 * M_PI * aProperties.mTwistRate;
			a = { std::sin(angle), r, std::cos(angle) };
			newdir2 = normalize(a);
		}

		float growAmount = aLevel * aLevel / (float)(aProperties.mLevels * aProperties.mLevels) * aProperties.mGrowAmount;
		float dropAmount = rLevel * aProperties.mDropAmount;
		float sweepAmount = rLevel * aProperties.mSweepAmount;
		a = { sweepAmount, dropAmount + growAmount, 0 };
		newdir = normalize(add(newdir, a));
		newdir2 = normalize(add(newdir2, a));

		fvec3 head0 = add(so, scaleVec(newdir, mLength));
		fvec3 head1 = add(so, scaleVec(newdir2, mLength));
		mChild0 = new Branch(head0, this);
		mChild1 = new Branch(head1, this);
		mChild0->mLength = pow(mLength, aProperties.mLengthFalloffPower) * aProperties.mLengthFalloffFactor;
		mChild1->mLength = pow(mLength, aProperties.mLengthFalloffPower) * aProperties.mLengthFalloffFactor;

		if (aLevel > 0)
		{
			if (aSteps > 0)
			{
				a = {
					(r - 0.5f) * 2 * aProperties.mTrunkKink,
					aProperties.mClimbRate,
					(r - 0.5f) * 2 * aProperties.mTrunkKink
				};
				mChild0->mHead = add(mHead, a);
				mChild0->mTrunktype = 1;
				mChild0->mLength = mLength * aProperties.mTaperRate;
				mChild0->split(aLevel, aSteps - 1, aProperties, aL1 + 1, aL2);
			}
			else
			{
				mChild0->split(aLevel - 1, 0, aProperties, aL1 + 1, aL2);
			}
			mChild1->split(aLevel - 1, 0, aProperties, aL1, aL2 + 1);
		}
	}


	Tree::Tree()
	{
		mRoot = 0;
		mVert = 0;
		mNormal = 0;
		mUV = 0;
		mTwigVert = 0;
		mTwigNormal = 0;
		mTwigUV = 0;
		mFace = 0;
		mTwigFace = 0;

		mVertCount = 0;
		mTwigVertCount = 0;
		mFaceCount = 0;
		mTwigFaceCount = 0;
	}

	Tree::~Tree()
	{
		delete[] mRoot;
		delete[] mVert;
		delete[] mNormal;
		delete[] mUV;
		delete[] mTwigVert;
		delete[] mTwigNormal;
		delete[] mTwigUV;
		delete[] mFace;
		delete[] mTwigFace;
	}

	void Tree::init()
	{
		mVertCount = 0;
		mTwigVertCount = 0;
		mFaceCount = 0;
		mTwigFaceCount = 0;

		delete[] mRoot;
		delete[] mVert;
		delete[] mNormal;
		delete[] mUV;
		delete[] mTwigVert;
		delete[] mTwigNormal;
		delete[] mTwigUV;
		delete[] mFace;
		delete[] mTwigFace;

		mRoot = 0;
		mVert = 0;
		mNormal = 0;
		mUV = 0;
		mTwigVert = 0;
		mTwigNormal = 0;
		mTwigUV = 0;
		mFace = 0;
		mTwigFace = 0;
	}

	void Tree::allocVertBuffers()
	{
		mVert = new fvec3[mVertCount];
		mNormal = new fvec3[mVertCount];
		mUV = new fvec2[mVertCount];
		mTwigVert = new fvec3[mTwigVertCount];
		mTwigNormal = new fvec3[mTwigVertCount];
		mTwigUV = new fvec2[mTwigVertCount];
		mTwigFace = new ivec3[mTwigFaceCount];

		// Reset back to zero, we'll use these as counters

		mVertCount = 0;
		mTwigVertCount = 0;
		mTwigFaceCount = 0;
	}

	void Tree::allocFaceBuffers()
	{
		mFace = new ivec3[mFaceCount];

		// Reset back to zero, we'll use these as counters

		mFaceCount = 0;
	}

	void Tree::generate()
	{
		init();
		mProperties.mRseed = mProperties.mSeed;
		fvec3 starthead = { 0, mProperties.mTrunkLength, 0 };
		mRoot = new Branch(starthead, 0);
		mRoot->mLength = mProperties.mInitialBranchLength;
		mRoot->split(mProperties.mLevels, mProperties.mTreeSteps, mProperties);

		calcVertSizes(0);
		allocVertBuffers();
		createForks(0, 0);
		createTwigs(0);
		calcFaceSizes(0);
		allocFaceBuffers();
		doFaces(0);
		calcNormals();
		fixUVs();
		delete mRoot;
		mRoot = 0;
	}

	void Tree::fixUVs()
	{
		// There'll never be more than 50% bad vertices
		int *badverttable = new int[mVertCount / 2];
		int i;
		int badverts = 0;

		// step 1: find bad verts
		// - If edge's U coordinate delta is over 0.5, texture has wrapped around. 
		// - The vertex that has zero U is the wrong one
		// - Care needs to be taken not to tag bad vertex more than once.

		for (i = 0; i < mFaceCount; i++)
		{
			// x/y edges (vertex 0 and 1)
			if ((std::fabs(mUV[mFace[i].x].u - mUV[mFace[i].y].u) > 0.5f) && (mUV[mFace[i].x].u == 0 || mUV[mFace[i].y].u == 0))
			{
				int found = 0, j;
				for (j = 0; j < badverts; j++)
				{
					if (badverttable[j] == mFace[i].y && mUV[mFace[i].y].u == 0)
						found = 1;
					if (badverttable[j] == mFace[i].x && mUV[mFace[i].x].u == 0)
						found = 1;
				}
				if (!found)
				{
					if (mUV[mFace[i].x].u == 0)
						badverttable[badverts] = mFace[i].x;
					if (mUV[mFace[i].y].u == 0)
						badverttable[badverts] = mFace[i].y;
					badverts++;
				}
			}

			// x/z edges (vertex 0 and 2)
			if ((std::fabs(mUV[mFace[i].x].u - mUV[mFace[i].z].u) > 0.5f) && (mUV[mFace[i].x].u == 0 || mUV[mFace[i].z].u == 0))
			{
				int found = 0, j;
				for (j = 0; j < badverts; j++)
				{
					if (badverttable[j] == mFace[i].z && mUV[mFace[i].z].u == 0)
						found = 1;
					if (badverttable[j] == mFace[i].x && mUV[mFace[i].x].u == 0)
						found = 1;
				}
				if (!found)
				{
					if (mUV[mFace[i].x].u == 0)
						badverttable[badverts] = mFace[i].x;
					if (mUV[mFace[i].z].u == 0)
						badverttable[badverts] = mFace[i].z;
					badverts++;
				}
			}

			// y/z edges (vertex 1 and 2)
			if ((std::fabs(mUV[mFace[i].y].u - mUV[mFace[i].z].u) > 0.5f) && (mUV[mFace[i].y].u == 0 || mUV[mFace[i].z].u == 0))
			{
				int found = 0, j;
				for (j = 0; j < badverts; j++)
				{
					if (badverttable[j] == mFace[i].z && mUV[mFace[i].z].u == 0)
						found = 1;
					if (badverttable[j] == mFace[i].y && mUV[mFace[i].y].u == 0)
						found = 1;
				}
				if (!found)
				{
					if (mUV[mFace[i].y].u == 0)
						badverttable[badverts] = mFace[i].y;
					if (mUV[mFace[i].z].u == 0)
						badverttable[badverts] = mFace[i].z;
					badverts++;
				}
			}
		}
		
		// step 2: allocate more space for our new duplicate verts

		fvec3 *nvert = new fvec3[mVertCount + badverts];
		memcpy(nvert, mVert, sizeof(fvec3) * mVertCount);
		delete[] mVert;
		mVert = nvert;

		fvec3 *nnorm = new fvec3[mVertCount + badverts];
		memcpy(nnorm, mNormal, sizeof(fvec3) * mVertCount);
		delete[] mNormal;
		mNormal = nnorm;

		fvec2 *nuv = new fvec2[mVertCount + badverts];
		memcpy(nuv, mUV, sizeof(fvec2) * mVertCount);
		delete[] mUV;
		mUV = nuv;

		// step 3: populate duplicate verts - otherwise identical except for U=1 instead of 0
		
		for (i = 0; i < badverts; i++)
		{
			mVert[mVertCount + i] = mVert[badverttable[i]];
			mNormal[mVertCount + i] = mNormal[badverttable[i]];
			mUV[mVertCount + i] = mUV[badverttable[i]];
			mUV[mVertCount + i].u = 1.0f;
		}

		// step 4: fix faces
		
		for (i = 0; i < mFaceCount; i++)
		{
			// x/y edges (vertex 0 and 1)
			if ((std::fabs(mUV[mFace[i].x].u - mUV[mFace[i].y].u) > 0.5f) && (mUV[mFace[i].x].u == 0 || mUV[mFace[i].y].u == 0))
			{				
				int found = 0, j;
				for (j = 0; j < badverts; j++)
				{
					if (badverttable[j] == mFace[i].y && mUV[mFace[i].y].u == 0)
						found = j;
					if (badverttable[j] == mFace[i].x && mUV[mFace[i].x].u == 0)
						found = j;
				}
				if (mUV[mFace[i].y].u == 0)
					mFace[i].y = mVertCount + found;
				if (mUV[mFace[i].x].u == 0)
					mFace[i].x = mVertCount + found;
			}

			// x/z edges (vertex 0 and 2)
			if ((std::fabs(mUV[mFace[i].x].u - mUV[mFace[i].z].u) > 0.5f) && (mUV[mFace[i].x].u == 0 || mUV[mFace[i].z].u == 0))
			{
				int found = 0, j;
				for (j = 0; j < badverts; j++)
				{
					if (badverttable[j] == mFace[i].z && mUV[mFace[i].z].u == 0)
						found = j;
					if (badverttable[j] == mFace[i].x && mUV[mFace[i].x].u == 0)
						found = j;
				}
				if (mUV[mFace[i].x].u == 0)
					mFace[i].x = mVertCount + found;
				if (mUV[mFace[i].z].u == 0)
					mFace[i].z = mVertCount + found;
			}

			// y/z edges (vertex 1 and 2)
			if ((std::fabs(mUV[mFace[i].y].u - mUV[mFace[i].z].u) > 0.5f) && (mUV[mFace[i].y].u == 0 || mUV[mFace[i].z].u == 0))
			{
				int found = 0, j;
				for (j = 0; j < badverts; j++)
				{
					if (badverttable[j] == mFace[i].z && mUV[mFace[i].z].u == 0)
						found = j;
					if (badverttable[j] == mFace[i].y && mUV[mFace[i].y].u == 0)
						found = j;
				}
				if (mUV[mFace[i].y].u == 0)
					mFace[i].y = mVertCount + found;
				if (mUV[mFace[i].z].u == 0)
					mFace[i].z = mVertCount + found;				
			}
		}

		// step 5: update vert count
		mVertCount += badverts;

		// and cleanup
		delete[] badverttable;
	}

	void Tree::calcVertSizes(Branch *aBranch)
	{
		int segments = mProperties.mSegments;
		if (!aBranch)
			aBranch = mRoot;

		if (!aBranch->mParent)
		{
			mVertCount += segments;
		}

		if (aBranch->mChild0)
		{
			mVertCount +=
				1 +
				(segments / 2) - 1 +
				1 +
				(segments / 2) - 1 +
				(segments / 2) - 1;

			calcVertSizes(aBranch->mChild0);
			calcVertSizes(aBranch->mChild1);
		}
		else
		{
			mVertCount++;
			mTwigVertCount += 8;
			mTwigFaceCount += 4;
		}
	}

	void Tree::calcFaceSizes(Branch *aBranch)
	{
		int segments = mProperties.mSegments;
		if (!aBranch)
			aBranch = mRoot;

		if (!aBranch->mParent)
		{
			mFaceCount += segments * 2;
		}

		if (aBranch->mChild0->mRing0 != 0)
		{
			mFaceCount += segments * 4;

			calcFaceSizes(aBranch->mChild0);
			calcFaceSizes(aBranch->mChild1);
		}
		else
		{
			mFaceCount += segments * 2;
		}
	}

	void Tree::calcNormals()
	{
		int *normalCount = new int[mVertCount];
		memset(normalCount, 0, sizeof(int) * mVertCount);
		memset(mNormal, 0, sizeof(fvec3) * mVertCount);

		int i;
		for (i = 0; i < (int)mFaceCount; i++)
		{
			normalCount[mFace[i].x]++;
			normalCount[mFace[i].y]++;
			normalCount[mFace[i].z]++;

			fvec3 norm = normalize(cross(sub(mVert[mFace[i].y], mVert[mFace[i].z]), sub(mVert[mFace[i].y], mVert[mFace[i].x])));

			mNormal[mFace[i].x].x += norm.x;
			mNormal[mFace[i].x].y += norm.y;
			mNormal[mFace[i].x].z += norm.z;
			mNormal[mFace[i].y].x += norm.x;
			mNormal[mFace[i].y].y += norm.y;
			mNormal[mFace[i].y].z += norm.z;
			mNormal[mFace[i].z].x += norm.x;
			mNormal[mFace[i].z].y += norm.y;
			mNormal[mFace[i].z].z += norm.z;
		}

		for (i = 0; i < (int)mVertCount; i++)
		{
			float d = 1.0f / normalCount[i];
			mNormal[i].x *= d;
			mNormal[i].y *= d;
			mNormal[i].z *= d;
		}

		delete[] normalCount;
	}

	void Tree::doFaces(Branch *aBranch)
	{
		if (!aBranch)
		{
			aBranch = mRoot;
		}
		int segments = mProperties.mSegments;
		int i;
		if (!aBranch->mParent)
		{
			fvec3 tangent = normalize(cross(sub(aBranch->mChild0->mHead, aBranch->mHead), sub(aBranch->mChild1->mHead, aBranch->mHead)));
			fvec3 normal = normalize(aBranch->mHead);
			fvec3 left = { -1, 0, 0 };
			float angle = std::acos(dot(tangent, left));
			if (dot(cross(left, tangent), normal) > 0)
			{
				angle = 2 * M_PI - angle;
			}
			int segOffset = (int)floor(0.5f + (angle / M_PI / 2 * segments));
			for (i = 0; i < segments; i++)
			{
				int v1 = aBranch->mRing0[i];
				int v2 = aBranch->mRootRing[(i + segOffset + 1) % segments];
				int v3 = aBranch->mRootRing[(i + segOffset) % segments];
				int v4 = aBranch->mRing0[(i + 1) % segments];

				ivec3 a;
				a = { v1, v4, v3 };
				mFace[mFaceCount++] = (a);
				a = { v4, v2, v3 };
				mFace[mFaceCount++] = (a);

				mUV[(i + segOffset) % segments] = { i / (float)segments, 0 };

				float len = length(sub(mVert[aBranch->mRing0[i]], mVert[aBranch->mRootRing[(i + segOffset) % segments]])) * mProperties.mVMultiplier;
				mUV[aBranch->mRing0[i]] = { i / (float)segments, len };
				mUV[aBranch->mRing2[i]] = { i / (float)segments, len };
			}
		}

		if (aBranch->mChild0->mRing0 != 0)
		{
			int segOffset0 = -1, segOffset1 = -1;
			float match0, match1;

			fvec3 v1 = normalize(sub(mVert[aBranch->mRing1[0]], aBranch->mHead));
			fvec3 v2 = normalize(sub(mVert[aBranch->mRing2[0]], aBranch->mHead));

			v1 = scaleInDirection(v1, normalize(sub(aBranch->mChild0->mHead, aBranch->mHead)), 0);
			v2 = scaleInDirection(v2, normalize(sub(aBranch->mChild1->mHead, aBranch->mHead)), 0);

			for (i = 0; i < segments; i++)
			{
				fvec3 d = normalize(sub(mVert[aBranch->mChild0->mRing0[i]], aBranch->mChild0->mHead));
				float l = dot(d, v1);
				if (segOffset0 == -1 || l > match0)
				{
					match0 = l;
					segOffset0 = segments - i;
				}
				d = normalize(sub(mVert[aBranch->mChild1->mRing0[i]], aBranch->mChild1->mHead));
				l = dot(d, v2);
				if (segOffset1 == -1 || l > match1)
				{
					match1 = l;
					segOffset1 = segments - i;
				}
			}

			float UVScale = mProperties.mMaxRadius / aBranch->mRadius;

			for (i = 0; i < segments; i++)
			{
				int v1 = aBranch->mChild0->mRing0[i];
				int v2 = aBranch->mRing1[(i + segOffset0 + 1) % segments];
				int v3 = aBranch->mRing1[(i + segOffset0) % segments];
				int v4 = aBranch->mChild0->mRing0[(i + 1) % segments];
				ivec3 a;
				a = { v1, v4, v3 };
				mFace[mFaceCount++] = (a);
				a = { v4, v2, v3 };
				mFace[mFaceCount++] = (a);

				v1 = aBranch->mChild1->mRing0[i];
				v2 = aBranch->mRing2[(i + segOffset1 + 1) % segments];
				v3 = aBranch->mRing2[(i + segOffset1) % segments];
				v4 = aBranch->mChild1->mRing0[(i + 1) % segments];

				a = { v1, v2, v3 };
				mFace[mFaceCount++] = (a);
				a = { v1, v4, v2 };
				mFace[mFaceCount++] = (a);

				float len1 = length(sub(mVert[aBranch->mChild0->mRing0[i]], mVert[aBranch->mRing1[(i + segOffset0) % segments]])) * UVScale;
				fvec2 uv1 = mUV[aBranch->mRing1[(i + segOffset0 - 1) % segments]];

				mUV[aBranch->mChild0->mRing0[i]] = { uv1.u, uv1.v + len1 * mProperties.mVMultiplier };
				mUV[aBranch->mChild0->mRing2[i]] = { uv1.u, uv1.v + len1 * mProperties.mVMultiplier };

				float len2 = length(sub(mVert[aBranch->mChild1->mRing0[i]], mVert[aBranch->mRing2[(i + segOffset1) % segments]])) * UVScale;
				fvec2 uv2 = mUV[aBranch->mRing2[(i + segOffset1 - 1) % segments]];

				mUV[aBranch->mChild1->mRing0[i]] = { uv2.u, uv2.v + len2 * mProperties.mVMultiplier };
				mUV[aBranch->mChild1->mRing2[i]] = { uv2.u, uv2.v + len2 * mProperties.mVMultiplier };
			}

			doFaces(aBranch->mChild0);
			doFaces(aBranch->mChild1);
		}
		else
		{
			for (i = 0; i < segments; i++)
			{
				ivec3 a;
				a = {
					aBranch->mChild0->mEnd,
					aBranch->mRing1[(i + 1) % segments],
					aBranch->mRing1[i]
				};
				mFace[mFaceCount++] = (a);
				a = {
					aBranch->mChild1->mEnd,
					aBranch->mRing2[(i + 1) % segments],
					aBranch->mRing2[i]
				};
				mFace[mFaceCount++] = (a);

				float len = length(sub(mVert[aBranch->mChild0->mEnd], mVert[aBranch->mRing1[i]]));
				mUV[aBranch->mChild0->mEnd] = { i / (float)segments - 1, len * mProperties.mVMultiplier };
				len = length(sub(mVert[aBranch->mChild1->mEnd], mVert[aBranch->mRing2[i]]));
				mUV[aBranch->mChild1->mEnd] = { i / (float)segments, len * mProperties.mVMultiplier };
			}
		}
	}

	void Tree::createTwigs(Branch *aBranch)
	{
		if (!aBranch)
		{
			aBranch = mRoot;
		}

		if (!aBranch->mChild0)
		{
			fvec3 tangent = normalize(cross(sub(aBranch->mParent->mChild0->mHead, aBranch->mParent->mHead), sub(aBranch->mParent->mChild1->mHead, aBranch->mParent->mHead)));
			fvec3 binormal = normalize(sub(aBranch->mHead, aBranch->mParent->mHead));
			//fvec3 normal = cross(tangent, binormal); //never used

			int vert1 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, mProperties.mTwigScale)), scaleVec(binormal, mProperties.mTwigScale * 2 - aBranch->mLength)));
			int vert2 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, -mProperties.mTwigScale)), scaleVec(binormal, mProperties.mTwigScale * 2 - aBranch->mLength)));
			int vert3 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, -mProperties.mTwigScale)), scaleVec(binormal, -aBranch->mLength)));
			int vert4 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, mProperties.mTwigScale)), scaleVec(binormal, -aBranch->mLength)));

			int vert8 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, mProperties.mTwigScale)), scaleVec(binormal, mProperties.mTwigScale * 2 - aBranch->mLength)));
			int vert7 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, -mProperties.mTwigScale)), scaleVec(binormal, mProperties.mTwigScale * 2 - aBranch->mLength)));
			int vert6 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, -mProperties.mTwigScale)), scaleVec(binormal, -aBranch->mLength)));
			int vert5 = mTwigVertCount;
			mTwigVert[mTwigVertCount++] = (add(add(aBranch->mHead, scaleVec(tangent, mProperties.mTwigScale)), scaleVec(binormal, -aBranch->mLength)));

			mTwigFace[mTwigFaceCount++] = { vert1, vert2, vert3 };
			mTwigFace[mTwigFaceCount++] = { vert4, vert1, vert3 };			
			mTwigFace[mTwigFaceCount++] = { vert6, vert7, vert8 };			
			mTwigFace[mTwigFaceCount++] = { vert6, vert8, vert5 };

			fvec3 normal = normalize(cross(sub(mTwigVert[vert1], mTwigVert[vert3]), sub(mTwigVert[vert2], mTwigVert[vert3])));
			fvec3 normal2 = normalize(cross(sub(mTwigVert[vert7], mTwigVert[vert6]), sub(mTwigVert[vert8], mTwigVert[vert6])));

			mTwigNormal[vert1] = (normal);
			mTwigNormal[vert2] = (normal);
			mTwigNormal[vert3] = (normal);
			mTwigNormal[vert4] = (normal);

			mTwigNormal[vert8] = (normal2);
			mTwigNormal[vert7] = (normal2);
			mTwigNormal[vert6] = (normal2);
			mTwigNormal[vert5] = (normal2);

			mTwigUV[vert1] = { 0, 0 };
			mTwigUV[vert2] = { 1, 0 };
			mTwigUV[vert3] = { 1, 1 };
			mTwigUV[vert4] = { 0, 1 };

			mTwigUV[vert8] = { 0, 0 };
			mTwigUV[vert7] = { 1, 0 };
			mTwigUV[vert6] = { 1, 1 };
			mTwigUV[vert5] = { 0, 1 };
		}
		else
		{
			createTwigs(aBranch->mChild0);
			createTwigs(aBranch->mChild1);
		}
	}

	void Tree::createForks(Branch *aBranch, float aRadius)
	{
		if (!aBranch) aBranch = mRoot;
		if (!aRadius) aRadius = mProperties.mMaxRadius;

		aBranch->mRadius = aRadius;

		if (aRadius > aBranch->mLength) aRadius = aBranch->mLength;

		int segments = mProperties.mSegments;

		float segmentAngle = M_PI * 2 / (float)segments;

		if (!aBranch->mParent)
		{
			aBranch->mRootRing = new int[segments];
			//create the root of the tree
			//branch.root = [];
			fvec3 axis = { 0, 1, 0 };
			int i;
			for (i = 0; i < segments; i++)
			{
				fvec3 left = { -1, 0, 0 };
				fvec3 vec = vecAxisAngle(left, axis, -segmentAngle * i);
				aBranch->mRootRing[i] = mVertCount;
				mVert[mVertCount++] = (scaleVec(vec, aRadius / mProperties.mRadiusFalloffRate));
			}
		}

		//cross the branches to get the left
		//add the branches to get the up
		if (aBranch->mChild0)
		{
			fvec3 axis;
			if (aBranch->mParent)
			{
				axis = normalize(sub(aBranch->mHead, aBranch->mParent->mHead));
			}
			else
			{
				axis = normalize(aBranch->mHead);
			}

			fvec3 axis1 = normalize(sub(aBranch->mHead, aBranch->mChild0->mHead));
			fvec3 axis2 = normalize(sub(aBranch->mHead, aBranch->mChild1->mHead));
			fvec3 tangent = normalize(cross(axis1, axis2));
			aBranch->mTangent = tangent;

			fvec3 axis3 = normalize(cross(tangent, normalize(add(scaleVec(axis1, -1), scaleVec(axis2, -1)))));
			fvec3 dir = { axis2.x, 0, axis2.z };
			fvec3 centerloc = add(aBranch->mHead, scaleVec(dir, -mProperties.mMaxRadius / 2));

			aBranch->mRing0 = new int[segments];
			aBranch->mRing1 = new int[segments];
			aBranch->mRing2 = new int[segments];

			int ring0count = 0;
			int ring1count = 0;
			int ring2count = 0;

			float scale = mProperties.mRadiusFalloffRate;

			if (aBranch->mChild0->mTrunktype || aBranch->mTrunktype)
			{
				scale = 1.0f / mProperties.mTaperRate;
			}

			//main segment ring
			int linch0 = mVertCount;
			aBranch->mRing0[ring0count++] = linch0;
			aBranch->mRing2[ring2count++] = linch0;
			mVert[mVertCount++] = (add(centerloc, scaleVec(tangent, aRadius * scale)));

			int start = mVertCount - 1;
			fvec3 d1 = vecAxisAngle(tangent, axis2, 1.57f);
			fvec3 d2 = normalize(cross(tangent, axis));
			float s = 1 / dot(d1, d2);
			int i;
			for (i = 1; i < segments / 2; i++)
			{
				fvec3 vec = vecAxisAngle(tangent, axis2, segmentAngle * i);
				aBranch->mRing0[ring0count++] = start + i;
				aBranch->mRing2[ring2count++] = start + i;
				vec = scaleInDirection(vec, d2, s);
				mVert[mVertCount++] = (add(centerloc, scaleVec(vec, aRadius * scale)));
			}
			int linch1 = mVertCount;
			aBranch->mRing0[ring0count++] = linch1;
			aBranch->mRing1[ring1count++] = linch1;
			mVert[mVertCount++] = (add(centerloc, scaleVec(tangent, -aRadius * scale)));
			for (i = segments / 2 + 1; i < segments; i++)
			{
				fvec3 vec = vecAxisAngle(tangent, axis1, segmentAngle * i);
				aBranch->mRing0[ring0count++] = mVertCount;
				aBranch->mRing1[ring1count++] = mVertCount;
				mVert[mVertCount++] = (add(centerloc, scaleVec(vec, aRadius * scale)));
			}
			aBranch->mRing1[ring1count++] = linch0; 
			aBranch->mRing2[ring2count++] = linch1; 
			start = mVertCount - 1;
			for (i = 1; i < segments / 2; i++)
			{
				fvec3 vec = vecAxisAngle(tangent, axis3, segmentAngle * i);
				aBranch->mRing1[ring1count++] = start + i;
				aBranch->mRing2[ring2count++] = start + (segments / 2 - i);
				fvec3 v = scaleVec(vec, aRadius * scale);
				mVert[mVertCount++] = (add(centerloc, v));
			}

			//child radius is related to the brans direction and the length of the branch
			//float length0 = length(sub(aBranch->mHead, aBranch->mChild0->mHead)); // never used
			//float length1 = length(sub(aBranch->mHead, aBranch->mChild1->mHead)); // never used

			float radius0 = 1 * aRadius * mProperties.mRadiusFalloffRate;
			float radius1 = 1 * aRadius * mProperties.mRadiusFalloffRate;
			if (aBranch->mChild0->mTrunktype)
			{
				radius0 = aRadius * mProperties.mTaperRate;
			}
			createForks(aBranch->mChild0, radius0);
			createForks(aBranch->mChild1, radius1);
		}
		else
		{
			//add points for the ends of braches
			aBranch->mEnd = mVertCount;
			//branch.head=add(branch.head,scaleVec([this.properties.xBias,this.properties.yBias,this.properties.zBias],branch.length*3));
			mVert[mVertCount++] = (aBranch->mHead);
		}
	}
}
