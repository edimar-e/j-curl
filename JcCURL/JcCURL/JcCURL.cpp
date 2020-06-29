#include "JcCURL.h"
#include <iostream>
#include <cstdio>
#include "curl/curl.h"



std::string str_res="unk";

static size_t cURL_Callback(void* data, size_t size, size_t nmemb, void* userp)
{
    size_t realsize = size * nmemb;
    //std::string* sp = static_cast<std::string*>(data);
    //str_res = *sp;
    //printf("\nvoid* data= %s, Metodo:%s\n", data, str_res.c_str());
    str_res = std::string((char*)data);
    
    return realsize;
}

jstring JNICALL Java_mainpkg_JcCURL_cURLget
(JNIEnv* env, jobject object, jstring param1) {
    CURL* curl;
    CURLcode res;
    jboolean isCopy1;
    std::string url;
    str_res = "GET";
    url = std::string(env->GetStringUTFChars(param1, &isCopy1));
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cURL_Callback);
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            //std::cout << str;
        }
        else { printf("Erro: res=%d\n", res); }

       curl_easy_cleanup(curl);
    } 
     return  env->NewStringUTF(str_res.c_str());
}

jstring JNICALL Java_mainpkg_JcCURL_cURLpost
(JNIEnv* env, jobject object, jstring param1, jstring param2) {
    jboolean isCopy1, isCopy2;
    std::string str1,str2;
    str1 = std::string(env->GetStringUTFChars(param1, &isCopy1));
    str2 = std::string(env->GetStringUTFChars(param2, &isCopy2));
    str_res = "POST";
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, str1.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str2.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(str2.c_str()));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cURL_Callback);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {

        }
        else{ printf("Erro: res=%d\n", res); }
        
        
    }

    curl_easy_cleanup(curl);
    return  env->NewStringUTF(str_res.c_str());
}

void JNICALL Java_mainpkg_JcCURL_teste
(JNIEnv* env, jobject object, jint param1) {
    CURL* curl;
    CURLcode res;
    std::string str = "0a";
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "localhost/curl.php?name=curljni2020");
        res = curl_easy_perform(curl);
        
    }
    curl_easy_cleanup(curl);
}
