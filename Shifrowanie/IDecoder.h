#pragma once
class IDecoder
{
public:
	virtual void Decode(bool hasWarning);
	virtual ~IDecoder() {};
};


