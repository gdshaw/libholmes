# libholmes

## Purpose

libholmes is a library for the forensic analysis of files and network
traffic.

## Intended capabilities

The library will allow artefacts (such as files and network packets) to be
parsed in a safe but permissive manner, disregarding errors and anomalies
unless they prevent the structure of the artefact from being determined.
This will result in an object tree which can be traversed and inspected,
providing access to all recognised artefact properties. It will also be
possible to:

* Validate artifacts, in order to detect less severe errors and anomalies
  which do not prevent the artefact from being parsed.
* Classify artefacts by comparing them against sets of pre-defined
  signatures.
* Convert artefacts to BSON or JSON, to facilitate processing by other
  systems.

## Current status

The library is currently in the early stages of development, and it
is not yet suitable for production use. None of the APIs should be
considered stable, and it is likely that future changes will be made
which break backward compatibility.

## Copyright and licensing

libholmes is copyright 2021 Graham Shaw.

Distribution and modification are permitted within the terms of the
GNU General Public License (version 3 or any later version).

Please refer to the file [LICENCE.md](LICENCE.md) for details.

Third-party contributions are not currently being accepted into the
upstream project.
