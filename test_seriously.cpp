#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Seriously.h"

#define BUFFER_SIZE 1024

TEST_CASE( "serialize/deserialize", "[serialize]" ) {
	SECTION( "for int32 give back the same value" ) {
		char buffer[BUFFER_SIZE];
		char *dstp = buffer;
		size_t avail = sizeof(buffer);
		ssize_t used;

		const int32_t original = 64591;
		int32_t reconstructed;
		used = seriously::Traits<int32_t>::serialize(dstp, avail, original);
		REQUIRE(used > 0);
		REQUIRE(used == 4);
		REQUIRE(avail >= 0);

		const char *srcp = buffer;
		avail = sizeof(buffer);

		used = seriously::Traits<int32_t>::deserialize(srcp, avail, reconstructed);
		REQUIRE(used > 0);
		REQUIRE(used == 4);
		REQUIRE(avail >= 0);

		REQUIRE(reconstructed == original);
	}
}

TEST_CASE( "Packer", "[Packer]" ) {
	SECTION( "basic API works" ) {
		seriously::Packer<BUFFER_SIZE> packer;

		const int32_t original1 = -64591;
		const bool original2 = true;
		const int8_t original3 = -112;
		const int16_t original4 = -2387;
		const int64_t original5 = -847564523LL;
		const uint32_t original6 = 934278945;
		const bool original7 = false;
		const int32_t original8 = 384752;
		const uint8_t original9 = 75;
		const std::string original10("this is a test!");
		const uint16_t original11 = 827;
		const std::string original12("Another string value.");
		const int32_t original13 = -464;
		const uint64_t original14 = 39824143232LL;
		const float original15 = -6.736;
		const double original16 = 4.736;

		std::vector<int16_t> original17;
		original17.push_back(9);
		original17.push_back(42);
		original17.push_back(11);

		std::vector<int64_t> original18;
		original18.push_back(9);
		original18.push_back(42);
		original18.push_back(11);

		std::vector<double> original19;
		original19.push_back(-6.736);
		original19.push_back(11.0);
		original19.push_back(4.736);
		original19.push_back(42.0);

		packer << original1 << original2 << original3 << original4 << original5 << original6 << original7 << original8 << original9 << original10 << original11 << original12 << original13 << original14 << original15 << original16 << original17 << original18 << original19;

		int32_t retrieved1;
		bool retrieved2;
		int8_t retrieved3;
		int16_t retrieved4;
		int64_t retrieved5;
		uint32_t retrieved6;
		bool retrieved7;
		int32_t retrieved8;
		uint8_t retrieved9;
		std::string retrieved10;
		uint16_t retrieved11;
		std::string retrieved12;
		int32_t retrieved13;
		uint64_t retrieved14;
		float retrieved15;
		double retrieved16;
		std::vector<int16_t> retrieved17;
		std::vector<int64_t> retrieved18;
		std::vector<double> retrieved19;

		packer >> retrieved1 >> retrieved2 >> retrieved3 >> retrieved4 >> retrieved5 >> retrieved6 >> retrieved7 >> retrieved8 >> retrieved9 >> retrieved10 >> retrieved11 >> retrieved12 >> retrieved13 >> retrieved14 >> retrieved15 >> retrieved16 >> retrieved17 >> retrieved18 >> retrieved19;

		REQUIRE(retrieved1 == original1);
		REQUIRE(retrieved2 == original2);
		REQUIRE(retrieved3 == original3);
		REQUIRE(retrieved4 == original4);
		REQUIRE(retrieved5 == original5);
		REQUIRE(retrieved6 == original6);
		REQUIRE(retrieved7 == original7);
		REQUIRE(retrieved8 == original8);
		REQUIRE(retrieved9 == original9);
		REQUIRE(retrieved10 == original10);
		REQUIRE(retrieved11 == original11);
		REQUIRE(retrieved12 == original12);
		REQUIRE(retrieved13 == original13);
		REQUIRE(retrieved14 == original14);
		REQUIRE(retrieved15 == original15);
		REQUIRE(retrieved16 == original16);
		REQUIRE(retrieved17 == original17);
		REQUIRE(retrieved18 == original18);
		REQUIRE(retrieved19 == original19);

		std::cerr << "used space: " << packer.size() << "bytes of " << packer.maxsize() << std::endl;

		REQUIRE(packer.unpacking_avail() == 0);
		REQUIRE(packer.packing_avail() > 0);
		REQUIRE(packer.packing_avail() == (packer.maxsize() - packer.size()));
	}

	SECTION( "intermixing packing and unpacking works" ) {
		seriously::Packer<BUFFER_SIZE> packer;

		const int32_t original1 = -64591;
		const bool original2 = true;
		const int8_t original3 = -112;
		const int16_t original4 = -2387;
		const int64_t original5 = -847564523LL;
		const uint32_t original6 = 934278945;
		const bool original7 = false;
		const int32_t original8 = 384752;
		const uint8_t original9 = 75;
		const std::string original10("this is a test!");
		const uint16_t original11 = 827;
		const std::string original12("Another string value.");
		const int32_t original13 = -464;
		const uint64_t original14 = 39824143232LL;
		const float original15 = -6.736;
		const double original16 = 4.736;

		int32_t retrieved1;
		bool retrieved2;
		int8_t retrieved3;
		int16_t retrieved4;
		int64_t retrieved5;
		uint32_t retrieved6;
		bool retrieved7;
		int32_t retrieved8;
		uint8_t retrieved9;
		std::string retrieved10;
		uint16_t retrieved11;
		std::string retrieved12;
		int32_t retrieved13;
		uint64_t retrieved14;
		float retrieved15;
		double retrieved16;

		packer << original1 << original2;

		packer >> retrieved1 >> retrieved2;

		packer << original3;
		packer << original4 << original5;
		packer << original6;

		packer >> retrieved3 >> retrieved4 >> retrieved5;

		packer >> retrieved6;

		packer << original7 << original8;
		packer << original9 << original10;

		packer >> retrieved7 >> retrieved8 >> retrieved9 >> retrieved10;

		packer << original11;
		packer << original12 << original13;
		packer << original14;

		packer >> retrieved11 >> retrieved12 >> retrieved13 >> retrieved14;

		packer << original15 << original16;

		packer >> retrieved15 >> retrieved16;

		REQUIRE(retrieved1 == original1);
		REQUIRE(retrieved2 == original2);
		REQUIRE(retrieved3 == original3);
		REQUIRE(retrieved4 == original4);
		REQUIRE(retrieved5 == original5);
		REQUIRE(retrieved6 == original6);
		REQUIRE(retrieved7 == original7);
		REQUIRE(retrieved8 == original8);
		REQUIRE(retrieved9 == original9);
		REQUIRE(retrieved10 == original10);
		REQUIRE(retrieved11 == original11);
		REQUIRE(retrieved12 == original12);
		REQUIRE(retrieved13 == original13);
		REQUIRE(retrieved14 == original14);
		REQUIRE(retrieved15 == original15);
		REQUIRE(retrieved16 == original16);
	}

	SECTION( "rewind unpacking works" ) {
		seriously::Packer<BUFFER_SIZE> packer;

		const int32_t original1 = -64591;
		const bool original2 = true;
		const int8_t original3 = -112;
		const int16_t original4 = -2387;
		const int64_t original5 = -847564523LL;
		const uint32_t original6 = 934278945;
		const bool original7 = false;
		const int32_t original8 = 384752;
		const uint8_t original9 = 75;
		const std::string original10("this is a test!");
		const uint16_t original11 = 827;
		const std::string original12("Another string value.");
		const int32_t original13 = -464;
		const uint64_t original14 = 39824143232LL;
		const float original15 = -6.736;
		const double original16 = 4.736;

		int32_t retrieved1;
		bool retrieved2;
		int8_t retrieved3;
		int16_t retrieved4;
		int64_t retrieved5;
		uint32_t retrieved6;
		bool retrieved7;
		int32_t retrieved8;
		uint8_t retrieved9;
		std::string retrieved10;
		uint16_t retrieved11;
		std::string retrieved12;
		int32_t retrieved13;
		uint64_t retrieved14;
		float retrieved15;
		double retrieved16;

		packer << original1 << original2;

		packer >> retrieved1 >> retrieved2;

		packer << original3;
		packer << original4 << original5;
		packer << original6;

		packer >> retrieved3 >> retrieved4 >> retrieved5;

		packer >> retrieved6;

		packer << original7 << original8;
		packer << original9 << original10;

		packer >> retrieved7 >> retrieved8 >> retrieved9 >> retrieved10;

		packer << original11;
		packer << original12 << original13;
		packer << original14;

		packer >> retrieved11 >> retrieved12 >> retrieved13 >> retrieved14;

		packer << original15 << original16;

		packer >> retrieved15 >> retrieved16;

		REQUIRE(retrieved1 == original1);
		REQUIRE(retrieved2 == original2);
		REQUIRE(retrieved3 == original3);
		REQUIRE(retrieved4 == original4);
		REQUIRE(retrieved5 == original5);
		REQUIRE(retrieved6 == original6);
		REQUIRE(retrieved7 == original7);
		REQUIRE(retrieved8 == original8);
		REQUIRE(retrieved9 == original9);
		REQUIRE(retrieved10 == original10);
		REQUIRE(retrieved11 == original11);
		REQUIRE(retrieved12 == original12);
		REQUIRE(retrieved13 == original13);
		REQUIRE(retrieved14 == original14);
		REQUIRE(retrieved15 == original15);
		REQUIRE(retrieved16 == original16);

		packer.unpacking_rewind();

		retrieved1 = 0;
		retrieved2 = false;
		retrieved3 = 0;
		retrieved4 = 0;
		retrieved5 = 0;
		retrieved6 = 0;
		retrieved7 = false;
		retrieved8 = 0;
		retrieved9 = 0;
		retrieved10 = "";
		retrieved11 = 0;
		retrieved12 = "";
		retrieved13 = 0;
		retrieved14 = 0;
		retrieved15 = 0.0;
		retrieved16 = 0.0;

		packer >> retrieved1 >> retrieved2 >> retrieved3 >> retrieved4 >> retrieved5 >> retrieved6 >> retrieved7 >> retrieved8 >> retrieved9 >> retrieved10 >> retrieved11 >> retrieved12 >> retrieved13 >> retrieved14 >> retrieved15 >> retrieved16;

		REQUIRE(retrieved1 == original1);
		REQUIRE(retrieved2 == original2);
		REQUIRE(retrieved3 == original3);
		REQUIRE(retrieved4 == original4);
		REQUIRE(retrieved5 == original5);
		REQUIRE(retrieved6 == original6);
		REQUIRE(retrieved7 == original7);
		REQUIRE(retrieved8 == original8);
		REQUIRE(retrieved9 == original9);
		REQUIRE(retrieved10 == original10);
		REQUIRE(retrieved11 == original11);
		REQUIRE(retrieved12 == original12);
		REQUIRE(retrieved13 == original13);
		REQUIRE(retrieved14 == original14);
		REQUIRE(retrieved15 == original15);
		REQUIRE(retrieved16 == original16);
	}

	SECTION( "setting up a Packer from raw data works" ) {
		seriously::Packer<BUFFER_SIZE> src_packer;

		const int32_t original1 = -64591;
		const bool original2 = true;
		const int8_t original3 = -112;
		const int16_t original4 = -2387;
		const int64_t original5 = -847564523LL;
		const std::string original10("this is a test!");
		src_packer << original1 << original2 << original3 << original4 << original5 << original10;

		seriously::Packer<BUFFER_SIZE> packer(src_packer.data(), src_packer.size());

		REQUIRE(packer.size() == src_packer.size());

		int32_t retrieved1;
		bool retrieved2;
		int8_t retrieved3;
		int16_t retrieved4;
		int64_t retrieved5;
		std::string retrieved10;

		packer >> retrieved1 >> retrieved2 >> retrieved3 >> retrieved4 >> retrieved5 >> retrieved10;

		REQUIRE(retrieved1 == original1);
		REQUIRE(retrieved2 == original2);
		REQUIRE(retrieved3 == original3);
		REQUIRE(retrieved4 == original4);
		REQUIRE(retrieved5 == original5);
		REQUIRE(retrieved10 == original10);
	}
}
