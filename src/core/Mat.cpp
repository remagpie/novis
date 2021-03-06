#include "core/Mat.h"

#include <vector>

#include "expect.hpp"

Napi::FunctionReference core::Mat::constructor;

void core::Mat::Init(Napi::Env env, Napi::Object exports) {
	auto func = DefineClass(env, "Mat", {
		InstanceMethod<&core::Mat::release>("release"),
		InstanceMethod<&core::Mat::width>("width"),
		InstanceMethod<&core::Mat::height>("height"),
	});

	core::Mat::constructor = Napi::Persistent(func);
	core::Mat::constructor.SuppressDestruct();

	exports.Set("Mat", func);
}

Napi::Object core::Mat::New(cv::Mat& mat) {
	auto result = core::Mat::constructor.New({});
	core::Mat::Unwrap(result)->setMat(mat);

	return result;
}

core::Mat::Mat(const Napi::CallbackInfo& info): Napi::ObjectWrap<core::Mat>(info) {
	this->alive = true;
}

core::Mat::~Mat() {
	if (this->alive) {
		this->mat.release();
	}
}

void core::Mat::setMat(cv::Mat mat) {
	if (this->alive) {
		this->mat.release();
	}
	this->mat = mat;
	this->alive = true;
}

void core::Mat::release(const Napi::CallbackInfo& info) {
	if (this->alive) {
		this->mat.release();
	}
	this->alive = false;
}

Napi::Value core::Mat::width(const Napi::CallbackInfo& info) {
	return Napi::Number::New(info.Env(), this->mat.cols);
}

Napi::Value core::Mat::height(const Napi::CallbackInfo& info) {
	return Napi::Number::New(info.Env(), this->mat.rows);
}
