"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

import cStringIO as StringIO
import struct

class tile_t(object):
    __slots__ = ["utime", "normal_direction", "origin", "x_axis_direction", "y_axis_direction", "width", "height"]

    def __init__(self):
        self.utime = 0
        self.normal_direction = [ 0.0 for dim0 in range(3) ]
        self.origin = [ 0.0 for dim0 in range(3) ]
        self.x_axis_direction = [ 0.0 for dim0 in range(3) ]
        self.y_axis_direction = [ 0.0 for dim0 in range(3) ]
        self.width = 0.0
        self.height = 0.0

    def encode(self):
        buf = StringIO.StringIO()
        buf.write(tile_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">q", self.utime))
        buf.write(struct.pack('>3d', *self.normal_direction[:3]))
        buf.write(struct.pack('>3d', *self.origin[:3]))
        buf.write(struct.pack('>3d', *self.x_axis_direction[:3]))
        buf.write(struct.pack('>3d', *self.y_axis_direction[:3]))
        buf.write(struct.pack(">dd", self.width, self.height))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = StringIO.StringIO(data)
        if buf.read(8) != tile_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return tile_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = tile_t()
        self.utime = struct.unpack(">q", buf.read(8))[0]
        self.normal_direction = struct.unpack('>3d', buf.read(24))
        self.origin = struct.unpack('>3d', buf.read(24))
        self.x_axis_direction = struct.unpack('>3d', buf.read(24))
        self.y_axis_direction = struct.unpack('>3d', buf.read(24))
        self.width, self.height = struct.unpack(">dd", buf.read(16))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if tile_t in parents: return 0
        tmphash = (0x15bbb03b9fa8d9d) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if tile_t._packed_fingerprint is None:
            tile_t._packed_fingerprint = struct.pack(">Q", tile_t._get_hash_recursive([]))
        return tile_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

