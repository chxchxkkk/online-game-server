// password_hash_gen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CryptoPP/sha.h"
#include "CryptoPP/base64.h"
#include <iostream>
#include <sstream>
#include <string>
#include <array>

int main()
{
	for (;;)
	{
		std::string password;
		std::cout << "enter password: ";
		std::getline(std::cin, password);

		CryptoPP::SHA1 sha;
		std::array<byte, CryptoPP::SHA1::DIGESTSIZE> hash;
		sha.CalculateDigest(hash.data(), (const byte*)password.data(), password.size());

		{
			std::string hash_b64;
			CryptoPP::Base64Encoder encoder{ new CryptoPP::StringSink{ hash_b64 } };

			encoder.Put(hash.data(), hash.size());
			encoder.MessageEnd();

			std::cout << "Base64-encoded password hash: " << hash_b64 << "\n";
		}

		{
			std::ostringstream ss;
			for (size_t i = 0; i < hash.size(); ++i)
			{
				ss.fill('0');
				ss.width(2);
				ss << std::hex << std::uppercase << (int)hash[i];
			}
			std::cout << "Base16-encoded password hash: " << ss.str() << "\n";
		}
	}

    return 0;
}

