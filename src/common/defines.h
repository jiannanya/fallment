#pragma once
#ifndef DEFINES_H
#define DEFINES_H


#include <iostream>
#include <memory>

#ifndef MAKE_PTR
#define MAKE_PTR(clazz) public: \
                                using Ptr = std::shared_ptr<clazz>; \
                                template<class... Args> \
                                inline static Ptr New(Args&&... args) { \
                                    return std::make_shared<clazz>(std::forward<Args>(args)...); \
                                }\

#endif

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}


#define glAssert(call) \
        do { \
            (call); \
            GLenum err = glGetError(); \
            if (err != GL_NO_ERROR) { \
                qDebug()<<"gl call error\n "; \
                std::cout<<"gl call error "<<" "<<err<<" "<<#call<<" "<<__FUNCTION__<<" "<<__LINE__<<std::endl; \
            } \
            else{ \
                \
            }\
        } while (0)

#endif