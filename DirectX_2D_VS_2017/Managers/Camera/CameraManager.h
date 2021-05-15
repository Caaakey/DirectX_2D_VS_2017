#pragma once

class CameraManager
{
public:
	static CameraManager* Get() {
		static CameraManager instance;
		return &instance;
	}

	CameraManager();
	CameraManager(CameraManager const&) = delete;
	~CameraManager();

	void operator=(CameraManager const&) = delete;
};

#define _Camera CameraManager::Get()