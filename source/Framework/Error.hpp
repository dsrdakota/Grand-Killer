#pragma once

#include <SFML/Graphics.hpp>

class Error
{
public:

	Error(const Error &) = delete;
	void operator=(const Error &) = delete;

	inline std::string* getErrorCommunicate() const { return errorCommunicate; }

	inline static Error& Instance()
	{
		static Error err;
		return err;
	}

	inline bool getErrorBool() const { return error; }

	void checkAllFiles();

	static void showCommunicate();
	std::string *errorCommunicate;

private:
	Error();
	~Error();

	bool error;

	template <class T >
	bool checkExist(const std::string &path, T *buffer);
};