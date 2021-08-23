#pragma once

#include <opencv2/opencv.hpp>
#include <napi.h>

class Mat: public Napi::ObjectWrap<Mat> {
public:
	static Napi::FunctionReference constructor;
	static void Init(Napi::Env env, Napi::Object exports);

private:
	bool alive;
	cv::Mat mat;

public:
	Mat(const Napi::CallbackInfo& info);
	~Mat();
	void setMat(cv::Mat mat);
	void release(const Napi::CallbackInfo& info);

	Napi::Value width(const Napi::CallbackInfo& info);
	Napi::Value height(const Napi::CallbackInfo& info);
};