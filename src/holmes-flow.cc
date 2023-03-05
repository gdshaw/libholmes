// This file is part of libholmes.
// Copyright 2023 Graham Shaw.
// Distribution and modification are permitted within the terms of the
// GNU General Public License (version 3 or any later version).

#include <cstdlib>
#include <iostream>

#include <getopt.h>

#include "holmes/octet/string.h"
#include "holmes/octet/file.h"
#include "holmes/pcap/file.h"
#include "holmes/net/ethernet/frame.h"
#include "holmes/net/inet4/datagram.h"
#include "holmes/net/tcp/segment.h"
#include "holmes/net/udp/datagram.h"
#include "holmes/net/inet/flow_table.h"
#include "holmes/net/decoder.h"

using namespace holmes;
using namespace holmes::net;

void write_help(std::ostream& out) {
	out << "Usage: holmes-flow <pathname>" << std::endl;
}

class flow_table_decoder final:
	public net::decoder {
private:
	net::inet::flow_table _flows;
protected:
	void handle_tcp(const inet::datagram& inet_dgram,
		const tcp::segment& tcp_seg) override;
public:
	void decode(const std::string& pathname);

	const net::inet::flow_table& flows() const {
		return _flows;
	}
};

void flow_table_decoder::handle_tcp(const inet::datagram& inet_dgram,
	const tcp::segment& tcp_seg) {

	_flows.ingest(inet_dgram, tcp_seg);
}

void flow_table_decoder::decode(const std::string& pathname) {
	try {
		octet::file file(pathname);
		pcap::file pf(file);

		while (true) {
			decode_ethernet(pf.read().payload());
		}
	} catch (std::out_of_range&) {
		/** No action. */
	}
}

int main(int argc, char* argv[]) {
	int opt;
	while ((opt = getopt(argc, argv, "j")) != -1) {
		switch (opt) {
		case 'j':
			break;
		}
	}

	if (optind == argc) {
		std::cerr << "PCAP file pathname not specified" << std::endl;
		exit(1);
	}

	try {
		flow_table_decoder decoder;
		while (optind != argc) {
			std::string pathname = argv[optind++];
			decoder.decode(pathname);
		}
		auto summary = decoder.flows().summarise();
		for (const auto& i : summary) {
			std::cout << i << std::endl;
		}

	} catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		exit(1);
	}
	return 0;
}
