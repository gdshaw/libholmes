#!/usr/bin/python3

import sys
import subprocess
import json

# Each test must include a 'data' member containing the data to be decoded,
# and an 'expected' member containing the expected result.
#
# All listed members and submembers of the expected result must be present
# in the observed result and must match. The observed result may contain
# additional members which are not listed. Order is not significant.

def compare(path, expected, observed):
    if isinstance(expected, dict):
        if not isinstance(observed, dict):
            raise AssertionError('%s not an object in result' % subpath)
        for key in expected:
            subpath = '.'.join([path, key]) if path else key
            if key in observed:
                compare(subpath, expected[key], observed[key])
            else:
                raise AssertionError('missing %s from result' % subpath)
    elif isinstance(expected, list):
        if not isinstance(observed, list):
            raise AssertionError('%s not a list in result' % subpath)
        for index in range(0, len(expected)):
            subpath = '.'.join([path, str(index)]) if path else str(index)
            compare(subpath, expected[index], observed[index])
    elif observed != expected:
        raise AssertionError('mismatch at %s: expected <%s>, found <%s>' %
            (path, expected, observed))

def test(pathname):
    file = open(pathname, "r")
    test = json.load(file)
    if "data" in test:
        data = test["data"]
        encoding = "-b"
    elif "hexdata" in test:
        data = test["hexdata"]
        encoding = "-x"
    else:
        raise KeyError("data/hexdata")
    expected = test["expected"]

    sp = subprocess.run(['holmes', 'decode', encoding, data], stdout=subprocess.PIPE)
    observed = json.loads(sp.stdout)
    compare('', expected, observed)

try:
    for pathname in sys.argv[1:]:
        test(pathname)
except AssertionError as ex:
    print('Error: %s' % ex)
    exit(1)
