"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

import cStringIO as StringIO
import struct

class click_coordinates_t(object):
    __slots__ = ["utime", "x", "y"]

    def __init__(self):
        self.utime = 0
        self.x = 0
        self.y = 0

    def encode(self):
        buf = StringIO.StringIO()
        buf.write(click_coordinates_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qqq", self.utime, self.x, self.y))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = StringIO.StringIO(data)
        if buf.read(8) != click_coordinates_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return click_coordinates_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = click_coordinates_t()
        self.utime, self.x, self.y = struct.unpack(">qqq", buf.read(24))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if click_coordinates_t in parents: return 0
        tmphash = (0x729c705be3058ec9) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if click_coordinates_t._packed_fingerprint is None:
            click_coordinates_t._packed_fingerprint = struct.pack(">Q", click_coordinates_t._get_hash_recursive([]))
        return click_coordinates_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

