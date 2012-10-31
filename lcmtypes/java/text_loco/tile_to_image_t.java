/* LCM type definition class file
 * This file was automatically generated by lcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

package text_loco;
 
import java.io.*;
import java.nio.*;
import java.util.*;
import lcm.lcm.*;
 
public final class tile_to_image_t implements lcm.lcm.LCMEncodable
{
    public long utime;
    public text_loco.tile_t tile;
    public long image_utime;
    public long x;
    public long y;
 
    public tile_to_image_t()
    {
    }
 
    public static final long LCM_FINGERPRINT;
    public static final long LCM_FINGERPRINT_BASE = 0x7fc331aa43705446L;
 
    static {
        LCM_FINGERPRINT = _hashRecursive(new ArrayList<Class>());
    }
 
    public static long _hashRecursive(ArrayList<Class> classes)
    {
        if (classes.contains(text_loco.tile_to_image_t.class))
            return 0L;
 
        classes.add(text_loco.tile_to_image_t.class);
        long hash = LCM_FINGERPRINT_BASE
             + text_loco.tile_t._hashRecursive(classes)
            ;
        classes.remove(classes.size() - 1);
        return (hash<<1) + ((hash>>63)&1);
    }
 
    public void encode(DataOutput outs) throws IOException
    {
        outs.writeLong(LCM_FINGERPRINT);
        _encodeRecursive(outs);
    }
 
    public void _encodeRecursive(DataOutput outs) throws IOException
    {
        outs.writeLong(this.utime); 
 
        this.tile._encodeRecursive(outs); 
 
        outs.writeLong(this.image_utime); 
 
        outs.writeLong(this.x); 
 
        outs.writeLong(this.y); 
 
    }
 
    public tile_to_image_t(byte[] data) throws IOException
    {
        this(new LCMDataInputStream(data));
    }
 
    public tile_to_image_t(DataInput ins) throws IOException
    {
        if (ins.readLong() != LCM_FINGERPRINT)
            throw new IOException("LCM Decode error: bad fingerprint");
 
        _decodeRecursive(ins);
    }
 
    public static text_loco.tile_to_image_t _decodeRecursiveFactory(DataInput ins) throws IOException
    {
        text_loco.tile_to_image_t o = new text_loco.tile_to_image_t();
        o._decodeRecursive(ins);
        return o;
    }
 
    public void _decodeRecursive(DataInput ins) throws IOException
    {
        this.utime = ins.readLong();
 
        this.tile = text_loco.tile_t._decodeRecursiveFactory(ins);
 
        this.image_utime = ins.readLong();
 
        this.x = ins.readLong();
 
        this.y = ins.readLong();
 
    }
 
    public text_loco.tile_to_image_t copy()
    {
        text_loco.tile_to_image_t outobj = new text_loco.tile_to_image_t();
        outobj.utime = this.utime;
 
        outobj.tile = this.tile.copy();
 
        outobj.image_utime = this.image_utime;
 
        outobj.x = this.x;
 
        outobj.y = this.y;
 
        return outobj;
    }
 
}

