#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef WIN32
#include <windows.h>
#endif
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>


#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1280
#endif
#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 720
#endif
#ifndef WINDOW_NAME
#define WINDOW_NAME "Hello OpenGL"
#endif

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>; \
using klassName ## UPtr = std::unique_ptr<klassName>; 


std::optional<std::string> LoadTextFile(const std::string& filename);

#endif 