// This file is part of libholmes.
// Copyright 2021 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <cstdlib>
#include <iostream>

#include <getopt.h>

#include "holmes/octet/string.h"
#include "holmes/octet/file.h"
#include "holmes/pcap/file.h"
#include "holmes/net/decoder.h"
#include "holmes/net/ethernet/frame.h"

using namespace holmes;

void write_help(std::ostream& out) {
	out << "Usage: holmes-decode <pathname>" << std::endl;
}

class bson_decoder final:
	public net::decoder {
private:
	bson::document* _out;
protected:
	void handle_artefact(const std::string& protocol,
		const artefact& af) override;
public:
	explicit bson_decoder(bson::document& out):
		_out(&out) {}
};

void bson_decoder::handle_artefact(const std::string& protocol,
	const artefact& af) {

	_out->append(protocol, af.to_bson());
}

bson::document decode(pcap::record rec) {
	bson::document result;
	bson_decoder decoder(result);
	decoder.decode_ethernet(rec.payload());
	return result;
}

void decode(const std::string& pathname, bool join) {
	if (join) {
		std::cout << '[';
	}

	bool first = true;
	try {
		octet::file file(pathname);
		pcap::file pf(file);

		while (true) {
			bson::document result;
			bson_decoder decoder(result);
			decoder.decode_ethernet(pf.read().payload());
			if (join) {
				if (first) {
					first = false;
				} else {
					std::cout << ',';
				}
			}
			std::cout << result.to_json();
			if (!join) {
				std::cout << '\n';
			}
		}
	} catch (std::out_of_range&) {
		/** No action. */
	}

	if (join) {
		std::cout << ']';
	}
}

int main(int argc, char* argv[]) {
	bool join = false;

	int opt;
	while ((opt = getopt(argc, argv, "j")) != -1) {
		switch (opt) {
		case 'j':
			join = true;
			break;
		}
	}

	if (optind == argc) {
		std::cerr << "PCAP file pathname not specified" << std::endl;
		std::exit(1);
	}
	std::string pathname = argv[optind++];

	try {
		decode(pathname, join);
	} catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		std::exit(1);
	}
	return 0;
}
