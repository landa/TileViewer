"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

import cStringIO as StringIO
import struct

import reference_line_segment_t

class reference_line_segment_set_t(object):
    __slots__ = ["utime", "linked_image_utime", "num_segments", "segments"]

    def __init__(self):
        self.utime = 0
        self.linked_image_utime = 0
        self.num_segments = 0
        self.segments = []

    def encode(self):
        buf = StringIO.StringIO()
        buf.write(reference_line_segment_set_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">qqi", self.utime, self.linked_image_utime, self.num_segments))
        for i0 in range(self.num_segments):
            self.segments[i0]._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = StringIO.StringIO(data)
        if buf.read(8) != reference_line_segment_set_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return reference_line_segment_set_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = reference_line_segment_set_t()
        self.utime, self.linked_image_utime, self.num_segments = struct.unpack(">qqi", buf.read(20))
        self.segments = []
        for i0 in range(self.num_segments):
            self.segments.append(reference_line_segment_t.reference_line_segment_t._decode_one(buf))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if reference_line_segment_set_t in parents: return 0
        newparents = parents + [reference_line_segment_set_t]
        tmphash = (0x3b86480b7e8f89c2+ reference_line_segment_t.reference_line_segment_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if reference_line_segment_set_t._packed_fingerprint is None:
            reference_line_segment_set_t._packed_fingerprint = struct.pack(">Q", reference_line_segment_set_t._get_hash_recursive([]))
        return reference_line_segment_set_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

