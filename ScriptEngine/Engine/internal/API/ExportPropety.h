#pragma once

#ifndef ENGINE_DLLEXPORT
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT __declspec(dllexport)
#endif