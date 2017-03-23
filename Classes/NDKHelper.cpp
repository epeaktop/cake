//  NDKHelper.cpp
#include "NDKHelper.h"
#include <vector>

#define NUM_MAX_LEN 10

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
    #include <android/log.h>
    #include <jni.h>
    #define  LOG_TAG    "DEBUG-NDKHELPER"
    #define CLASS_NAME "org/cocos2dx/cpp/AndroidNDKHelper"
#endif

extern "C"
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::vector<std::string> split(std::string str,std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		str += pattern; //扩展字符串以方便操作
		int size = str.size();

		for(int i = 0; i < size; i++)
		{   
			pos=str.find(pattern, i); 
			if(pos < size)
			{   
				std::string s = str.substr(i,pos-i);
				result.push_back(s);
				i = pos + pattern.size()-1;
			}   
		}   

		return result;
	}
	/** 
	 * desc: 响应java层的函数，java调用过的东西都会经过这里，这里去抛事件 
	 * 协议 methodName,methodParams0,methodName1,...,methodNamen
	 */
	void Java_org_cocos2dx_lib_AndroidNDKHelper_CPPNativeCallHandler(JNIEnv* env, jobject thiz, jstring json)
	{
		string jsonString = JniHelper::jstring2string(json);
		vector<string> rst = split(jsonString, string(","));
		string methodName =  rst[0];
		std::string::size_type pos = jsonString.find(",");

		string methodParams = jsonString;
		if(pos == jsonString.npos)
		{
			methodParams = "__jni-no-args__";   	
		}

		if(jsonString.length() - pos >  1)
		{
			methodParams = jsonString.substr(pos + 1, jsonString.length() - pos - 1);
		}
		else
		{
			methodParams = "__jni-error-format__";
		}


		__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s,%s", methodName.c_str(), methodParams.c_str());

	}
#endif

	// Method for sending message from CPP to the targetted platform
	void callJava(string methodName, string methodParams)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (0 == strcmp(methodName.c_str(), ""))
			return;

		JniMethodInfo t;
		string tmp = methodName + "," + methodParams;
		log(">>>>>> SendMessageWithParams:%s <<<<<<" , tmp.c_str());

		if (JniHelper::getStaticMethodInfo(t,
					CLASS_NAME,
					"RecieveCppMessage",
					"(Ljava/lang/String;)V"))
		{

			jstring stringArg1 = t.env->NewStringUTF(tmp.c_str());
			t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
			t.env->DeleteLocalRef(stringArg1);
			t.env->DeleteLocalRef(t.classID);
		}
#endif
	}
} // end extern "C"



