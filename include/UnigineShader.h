/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */

// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UniginePtr.h"
#include "UnigineMathLib.h"

namespace Unigine
{


class UNIGINE_API Shader : public APIInterface
{
public:
	static Ptr<Shader> create();
	static Ptr<Shader> create(const char *name);
	static Ptr<Shader> create(const char *name, const char *defines);
	static Ptr<Shader> create(const char *vertex, const char *fragment, const char *defines);
	bool loadVertex(const char *name, const char *defines) const;
	bool loadControl(const char *name, const char *defines) const;
	bool loadEvaluate(const char *name, const char *defines) const;
	bool loadGeometry(const char *name, const char *defines) const;
	bool loadFragment(const char *name, const char *defines) const;
	bool loadCompute(const char *name, const char *defines) const;
	bool compile() const;
	void clear() const;
	void destroy() const;
	int findParameter(int fast_id);
	int findParameter(const char *name);
	int findParameter(const char *name, int fast_id);
	void setParameterFloat(int id, float value);
	void setParameterFloat(const char *name, float value);
	void setParameterFloat(const char *name, int fast_id, float value);
	void setParameterFloat2(int id, const Math::vec2 &value);
	void setParameterFloat2(const char *name, const Math::vec2 &value);
	void setParameterFloat2(const char *name, int fast_id, const Math::vec2 &value);
	void setParameterFloat3(int id, const Math::vec3 &value);
	void setParameterFloat3(const char *name, const Math::vec3 &value);
	void setParameterFloat3(const char *name, int fast_id, const Math::vec3 &value);
	void setParameterFloat4(int id, const Math::vec4 &value);
	void setParameterFloat4(const char *name, const Math::vec4 &value);
	void setParameterFloat4(const char *name, int fast_id, const Math::vec4 &value);
	void setParameterFloat3x3(int id, const Math::mat3 & value);
	void setParameterFloat3x3(const char *name, const Math::mat3 & value);
	void setParameterFloat3x3(const char *name, int fast_id, const Math::mat3 & value);
	void setParameterFloat4x4(int id, const Math::mat4 &value);
	void setParameterFloat4x4(const char *name, const Math::mat4 &value);
	void setParameterFloat4x4(const char *name, int fast_id, const Math::mat4 &value);
	void setParameterInt(int id, int value);
	void setParameterInt(const char *name, int value);
	void setParameterInt(const char *name, int fast_id, int value);
	void setParameterInt2(int id, const Math::ivec2 &value);
	void setParameterInt2(const char *name, const Math::ivec2 &value);
	void setParameterInt2(const char *name, int fast_id, const Math::ivec2 &value);
	void setParameterInt3(int id, const Math::ivec3 &value);
	void setParameterInt3(const char *name, const Math::ivec3 &value);
	void setParameterInt3(const char *name, int fast_id, const Math::ivec3 &value);
	void setParameterInt4(int id, const Math::ivec4 &value);
	void setParameterInt4(const char *name, const Math::ivec4 &value);
	void setParameterInt4(const char *name, int fast_id, const Math::ivec4 &value);
	void setParameterDouble(int id, double value);
	void setParameterDouble(const char *name, double value);
	void setParameterDouble(const char *name, int fast_id, double value);
	void setParameterDouble2(int id, const Math::dvec2 &value);
	void setParameterDouble2(const char *name, const Math::dvec2 &value);
	void setParameterDouble2(const char *name, int fast_id, const Math::dvec2 &value);
	void setParameterDouble3(int id, const Math::dvec3 &value);
	void setParameterDouble3(const char *name, const Math::dvec3 &value);
	void setParameterDouble3(const char *name, int fast_id, const Math::dvec3 &value);
	void setParameterDouble4(int id, const Math::dvec4 &value);
	void setParameterDouble4(const char *name, const Math::dvec4 &value);
	void setParameterDouble4(const char *name, int fast_id, const Math::dvec4 &value);
	void setParameterDouble4x4(int id, const Math::dmat4 &value);
	void setParameterDouble4x4(const char *name, const Math::dmat4 &value);
	void setParameterDouble4x4(const char *name, int fast_id, const Math::dmat4 &value);
	void setParameterScalar(int id, Math::Scalar value);
	void setParameterScalar(const char *name, Math::Scalar value);
	void setParameterScalar(const char *name, int fast_id, Math::Scalar value);
	void setParameterScalar2(int id, const Math::Vec2 & value);
	void setParameterScalar2(const char *name, const Math::Vec2 & value);
	void setParameterScalar2(const char *name, int fast_id, const Math::Vec2 & value);
	void setParameterScalar3(int id, const Math::Vec3 & value);
	void setParameterScalar3(const char *name, const Math::Vec3 & value);
	void setParameterScalar3(const char *name, int fast_id, const Math::Vec3 & value);
	void setParameterScalar4(int id, const Math::Vec4 & value);
	void setParameterScalar4(const char *name, const Math::Vec4 & value);
	void setParameterScalar4(const char *name, int fast_id, const Math::Vec4 & value);
	void setParameterArrayFloat(int id, const float * value, int num_elements);
	void setParameterArrayFloat(const char *name, const float * value, int num_elements);
	void setParameterArrayFloat(const char *name, int fast_id, const float * value, int num_elements);
	void setParameterArrayFloat(int id, const Vector< float > &value);
	void setParameterArrayFloat(const char *name, const Vector< float > &value);
	void setParameterArrayFloat(const char *name, int fast_id, const Vector< float > &value);
	void setParameterArrayFloat2(int id, const Math::vec2 * value, int num_elements);
	void setParameterArrayFloat2(const char *name, const Math::vec2 * value, int num_elements);
	void setParameterArrayFloat2(const char *name, int fast_id, const Math::vec2 * value, int num_elements);
	void setParameterArrayFloat2(int id, const Vector< Math::vec2 > &value);
	void setParameterArrayFloat2(const char *name, const Vector< Math::vec2 > &value);
	void setParameterArrayFloat2(const char *name, int fast_id, const Vector< Math::vec2 > &value);
	void setParameterArrayFloat4(int id, const Math::vec4 * value, int num_elements);
	void setParameterArrayFloat4(const char *name, const Math::vec4 * value, int num_elements);
	void setParameterArrayFloat4(const char *name, int fast_id, const Math::vec4 * value, int num_elements);
	void setParameterArrayFloat4(int id, const Vector< Math::vec4 > &value);
	void setParameterArrayFloat4(const char *name, const Vector< Math::vec4 > &value);
	void setParameterArrayFloat4(const char *name, int fast_id, const Vector< Math::vec4 > &value);
	void setParameterArrayFloat4x4(int id, const Math::mat4 * value, int num_elements);
	void setParameterArrayFloat4x4(const char *name, const Math::mat4 * value, int num_elements);
	void setParameterArrayFloat4x4(const char *name, int fast_id, const Math::mat4 * value, int num_elements);
	void setParameterArrayFloat4x4(int id, const Vector< Math::mat4 > &value);
	void setParameterArrayFloat4x4(const char *name, const Vector< Math::mat4 > &value);
	void setParameterArrayFloat4x4(const char *name, int fast_id, const Vector< Math::mat4 > &value);
	void setParameterArrayInt(int id, const int * value, int num_elements);
	void setParameterArrayInt(const char *name, const int * value, int num_elements);
	void setParameterArrayInt(const char *name, int fast_id, const int * value, int num_elements);
	void setParameterArrayInt(int id, const Vector< int > &value);
	void setParameterArrayInt(const char *name, const Vector< int > &value);
	void setParameterArrayInt(const char *name, int fast_id, const Vector< int > &value);
	void setParameterArrayInt2(int id, const Math::ivec2 * value, int num_elements);
	void setParameterArrayInt2(const char *name, const Math::ivec2 * value, int num_elements);
	void setParameterArrayInt2(const char *name, int fast_id, const Math::ivec2 * value, int num_elements);
	void setParameterArrayInt2(int id, const Vector< Math::ivec2 > &value);
	void setParameterArrayInt2(const char *name, const Vector< Math::ivec2 > &value);
	void setParameterArrayInt2(const char *name, int fast_id, const Vector< Math::ivec2 > &value);
	void setParameterArrayInt4(int id, const Math::ivec4 * value, int num_elements);
	void setParameterArrayInt4(const char *name, const Math::ivec4 * value, int num_elements);
	void setParameterArrayInt4(const char *name, int fast_id, const Math::ivec4 * value, int num_elements);
	void setParameterArrayInt4(int id, const Vector< Math::ivec4 > &value);
	void setParameterArrayInt4(const char *name, const Vector< Math::ivec4 > &value);
	void setParameterArrayInt4(const char *name, int fast_id, const Vector< Math::ivec4 > &value);
	void setParameterArrayDouble(int id, const double * value, int num_elements);
	void setParameterArrayDouble(const char *name, const double * value, int num_elements);
	void setParameterArrayDouble(const char *name, int fast_id, const double * value, int num_elements);
	void setParameterArrayDouble(int id, const Vector< double > &value);
	void setParameterArrayDouble(const char *name, const Vector< double > &value);
	void setParameterArrayDouble(const char *name, int fast_id, const Vector< double > &value);
	void setParameterArrayDouble2(int id, const Math::dvec2 * value, int num_elements);
	void setParameterArrayDouble2(const char *name, const Math::dvec2 * value, int num_elements);
	void setParameterArrayDouble2(const char *name, int fast_id, const Math::dvec2 * value, int num_elements);
	void setParameterArrayDouble2(int id, const Vector< Math::dvec2 > &value);
	void setParameterArrayDouble2(const char *name, const Vector< Math::dvec2 > &value);
	void setParameterArrayDouble2(const char *name, int fast_id, const Vector< Math::dvec2 > &value);
	void setParameterArrayDouble4(int id, const Math::dvec4 * value, int num_elements);
	void setParameterArrayDouble4(const char *name, const Math::dvec4 * value, int num_elements);
	void setParameterArrayDouble4(const char *name, int fast_id, const Math::dvec4 * value, int num_elements);
	void setParameterArrayDouble4(int id, const Vector< Math::dvec4 > &value);
	void setParameterArrayDouble4(const char *name, const Vector< Math::dvec4 > &value);
	void setParameterArrayDouble4(const char *name, int fast_id, const Vector< Math::dvec4 > &value);
	void flushParameters() const;
	void bind() const;
	void unbind() const;
	int getGLProgramID() const;
	void * getD3D11VertexShader() const;
	void * getD3D11ControlShader() const;
	void * getD3D11EvaluateShader() const;
	void * getD3D11GeometryShader() const;
	void * getD3D11FragmentShader() const;
	void * getD3D11ComputeShader() const;
};
typedef Ptr<Shader> ShaderPtr;

} // namespace Unigine
