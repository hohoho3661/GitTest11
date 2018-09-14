#include "stdafx.h"
#include "Animation.h"
#include "Image.h"


Animation::Animation()
{
}


Animation::~Animation()
{
}

bool Animation::Init(int totlaW, int totalH, int frameW, int frameH)
{
	return false;
}

bool Animation::Init(Image * image)
{
	return false;
}

void Animation::Release()
{
}

void Animation::setDefPlayFrame(bool reverse, bool loop)
{
}

void Animation::setPlayFrame(int * playArr, int arLen, bool loop)
{
}

void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
}

void Animation::setFPS(int framePerSec)
{
}

void Animation::frameUpdate(float elapsedTime)
{
}

void Animation::start()
{
}

void Animation::stop()
{
}

void Animation::pause()
{
}

void Animation::rsume()
{
}
