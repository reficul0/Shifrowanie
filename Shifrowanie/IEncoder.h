#pragma once
class IEncoder
{
public:
	virtual void Encode(bool hasWarning) {}
	virtual ~IEncoder() {}
};
