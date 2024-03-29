/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <string.h>
#include "lcmtypes/text_loco_reference_line_segment_t.h"

static int __text_loco_reference_line_segment_t_hash_computed;
static int64_t __text_loco_reference_line_segment_t_hash;

int64_t __text_loco_reference_line_segment_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __text_loco_reference_line_segment_t_get_hash)
            return 0;

    const __lcm_hash_ptr cp = { p, (void*)__text_loco_reference_line_segment_t_get_hash };
    (void) cp;

    int64_t hash = 0xfc2d743d6fad96faLL
         + __double_hash_recursive(&cp)
         + __double_hash_recursive(&cp)
         + __double_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __text_loco_reference_line_segment_t_get_hash(void)
{
    if (!__text_loco_reference_line_segment_t_hash_computed) {
        __text_loco_reference_line_segment_t_hash = __text_loco_reference_line_segment_t_hash_recursive(NULL);
        __text_loco_reference_line_segment_t_hash_computed = 1;
    }

    return __text_loco_reference_line_segment_t_hash;
}

int __text_loco_reference_line_segment_t_encode_array(void *buf, int offset, int maxlen, const text_loco_reference_line_segment_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __double_encode_array(buf, offset + pos, maxlen - pos, p[element].start, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_encode_array(buf, offset + pos, maxlen - pos, p[element].end, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_encode_array(buf, offset + pos, maxlen - pos, p[element].reference_origin, 3);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int text_loco_reference_line_segment_t_encode(void *buf, int offset, int maxlen, const text_loco_reference_line_segment_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __text_loco_reference_line_segment_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __text_loco_reference_line_segment_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __text_loco_reference_line_segment_t_encoded_array_size(const text_loco_reference_line_segment_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __double_encoded_array_size(p[element].start, 3);

        size += __double_encoded_array_size(p[element].end, 3);

        size += __double_encoded_array_size(p[element].reference_origin, 3);

    }
    return size;
}

int text_loco_reference_line_segment_t_encoded_size(const text_loco_reference_line_segment_t *p)
{
    return 8 + __text_loco_reference_line_segment_t_encoded_array_size(p, 1);
}

int __text_loco_reference_line_segment_t_decode_array(const void *buf, int offset, int maxlen, text_loco_reference_line_segment_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __double_decode_array(buf, offset + pos, maxlen - pos, p[element].start, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_decode_array(buf, offset + pos, maxlen - pos, p[element].end, 3);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __double_decode_array(buf, offset + pos, maxlen - pos, p[element].reference_origin, 3);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __text_loco_reference_line_segment_t_decode_array_cleanup(text_loco_reference_line_segment_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __double_decode_array_cleanup(p[element].start, 3);

        __double_decode_array_cleanup(p[element].end, 3);

        __double_decode_array_cleanup(p[element].reference_origin, 3);

    }
    return 0;
}

int text_loco_reference_line_segment_t_decode(const void *buf, int offset, int maxlen, text_loco_reference_line_segment_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __text_loco_reference_line_segment_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __text_loco_reference_line_segment_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int text_loco_reference_line_segment_t_decode_cleanup(text_loco_reference_line_segment_t *p)
{
    return __text_loco_reference_line_segment_t_decode_array_cleanup(p, 1);
}

int __text_loco_reference_line_segment_t_clone_array(const text_loco_reference_line_segment_t *p, text_loco_reference_line_segment_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __double_clone_array(p[element].start, q[element].start, 3);

        __double_clone_array(p[element].end, q[element].end, 3);

        __double_clone_array(p[element].reference_origin, q[element].reference_origin, 3);

    }
    return 0;
}

text_loco_reference_line_segment_t *text_loco_reference_line_segment_t_copy(const text_loco_reference_line_segment_t *p)
{
    text_loco_reference_line_segment_t *q = (text_loco_reference_line_segment_t*) malloc(sizeof(text_loco_reference_line_segment_t));
    __text_loco_reference_line_segment_t_clone_array(p, q, 1);
    return q;
}

void text_loco_reference_line_segment_t_destroy(text_loco_reference_line_segment_t *p)
{
    __text_loco_reference_line_segment_t_decode_array_cleanup(p, 1);
    free(p);
}

int text_loco_reference_line_segment_t_publish(lcm_t *lc, const char *channel, const text_loco_reference_line_segment_t *p)
{
      int max_data_size = text_loco_reference_line_segment_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = text_loco_reference_line_segment_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _text_loco_reference_line_segment_t_subscription_t {
    text_loco_reference_line_segment_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void text_loco_reference_line_segment_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    text_loco_reference_line_segment_t p;
    memset(&p, 0, sizeof(text_loco_reference_line_segment_t));
    status = text_loco_reference_line_segment_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding text_loco_reference_line_segment_t!!!\n", status);
        return;
    }

    text_loco_reference_line_segment_t_subscription_t *h = (text_loco_reference_line_segment_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    text_loco_reference_line_segment_t_decode_cleanup (&p);
}

text_loco_reference_line_segment_t_subscription_t* text_loco_reference_line_segment_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    text_loco_reference_line_segment_t_handler_t f, void *userdata)
{
    text_loco_reference_line_segment_t_subscription_t *n = (text_loco_reference_line_segment_t_subscription_t*)
                       malloc(sizeof(text_loco_reference_line_segment_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 text_loco_reference_line_segment_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg text_loco_reference_line_segment_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int text_loco_reference_line_segment_t_subscription_set_queue_capacity (text_loco_reference_line_segment_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int text_loco_reference_line_segment_t_unsubscribe(lcm_t *lcm, text_loco_reference_line_segment_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe text_loco_reference_line_segment_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}

