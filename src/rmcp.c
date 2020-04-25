/*
Copyright (c) 2020 matt pallissard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rmcp.h>

uint64_t unpackl(uint8_t *d, size_t l)
{
	/*
	* pull arbitrary bits out of a given location
	* big endian, MSB first
	*/
	uint64_t j = 0;
	do {
		l--;
		j |= (uint64_t)(d)[l] << l * 8;
	} while (l);
	return j;
}

uint64_t unpackr(uint8_t *d, size_t l)
{
	/*
	* pull arbitrary bits out of a given location
	* little endian, LSB first
	*/
	size_t i = l;
	size_t j = 0;
	uint64_t r = 0;
	do {
		r |= (uint64_t)(d)[--i] << j++ * 8;
	} while (j < l);
	return r;
}
void packl(uint8_t *d, uint64_t s, size_t l)
{
	/*
	* pack arbitrary bytes (s) into a location (d)
	* big endian, MSB first
	*/
	do {
		--l;
		(d)[l] = s >> 8 * l;
	} while (l);
}

void packr(uint8_t *d, uint64_t s, size_t l)
{
	/*
	* pack arbitrary bytes (s) into a location (d),
	* little endian, LSB first.
	*/
	do {
		(d)[--l] = s;
		s >>= 8;
	} while (l);
}

uint32_t asf_msg_data_get_iana(struct asf_data *a)
{
	return a->iana_number;
}

uint32_t asf_msg_data_get_oem(struct asf_data *a)
{
	return a->oem_defined;
}

uint8_t asf_msg_data_get_supported_entities_ipmi(struct asf_data *a)
{
	return a->supported_entities >> 7;
}

uint8_t asf_msg_data_get_supported_entities_version(struct asf_data *a)
{
	/*
	* 3 bits, 0-3
	*/
	return a->supported_entities & 7;
}

uint8_t asf_msg_data_get_supported_interactions_security(struct asf_data *a)
{
	/*
	 * one bit, 7
	 */
	return a->supported_interactions >> 7;
}

uint8_t asf_msg_data_get_supported_interactions_dash(struct asf_data *a)
{
	/*
	* one bit, 5
	*/
	return (a->supported_interactions & 32) >> 5;
}
void asf_msg_data_set_iana(struct asf_data *a, uint32_t i)
{
	a->iana_number = i;
}

void asf_msg_data_set_oem(struct asf_data *a, uint32_t i)
{
	a->oem_defined = i;
}
void asf_msg_data_set_supported_entities_ipmi(struct asf_data *a, uint32_t i)
{
	/*
	* one bit, high bit
	*/
	a->supported_entities &= 127;
	a->supported_entities |= i << 7;
}

void asf_msg_data_set_supported_entities_version(struct asf_data *a)
{
	/*
	* three bits, low bits
	*/
	a->supported_entities &= 252;
	a->supported_entities |= 1;
}

void asf_msg_data_set_supported_interactions_security(struct asf_data *a, uint8_t i)
{
	/*
	* one bit, 7
	*/
	a->supported_interactions &= 127;
	a->supported_interactions |= i << 7;
}

void asf_msg_data_set_supported_interactions_dash(struct asf_data *a, uint8_t i)
{
	/*
	* one bit, 5
	*/
	a->supported_interactions &= ~32;
	a->supported_interactions |= i << 5;
}

void asf_msg_data_set_supported_interactions_reserved(struct asf_data *a)
{
	/*
	*  bits 0-4, 6 are reserved, set to 0;
	*/
	a->supported_interactions &= ~95;
}

void asf_msg_data_pack_iana(uint8_t *d, struct asf_data *a)
{
	packr(&(d)[ASF_MSG_DATA_IANA_OFFSET], a->iana_number, ASF_MSG_DATA_IANA_SIZE);
}

void asf_msg_data_pack_oem(uint8_t *d, struct asf_data *a)
{
	packr(&(d)[ASF_MSG_DATA_OEM_OFFSET], a->oem_defined, ASF_MSG_DATA_OEM_SIZE);
}

void asf_msg_data_pack_supported_entities(uint8_t *d, struct asf_data *a)
{
	packr(&(d)[ASF_MSG_DATA_SUP_ENT_OFFSET], a->supported_entities, ASF_MSG_DATA_SUP_ENT_SIZE);
}

void asf_msg_data_pack_supported_interactions(uint8_t *d, struct asf_data *a)
{
	packr(&(d)[ASF_MSG_DATA_SUP_INT_OFFSET], a->supported_interactions, ASF_MSG_DATA_SUP_INT_SIZE);
}
void asf_msg_data_unpack_iana(uint8_t *d, struct asf_data *a)
{
	a->iana_number = unpackr(&(d)[ASF_MSG_DATA_IANA_OFFSET], ASF_MSG_DATA_IANA_SIZE);
}

void asf_msg_data_unpack_oem(uint8_t *d, struct asf_data *a)
{
	a->oem_defined = unpackr(&(d)[ASF_MSG_DATA_OEM_OFFSET], ASF_MSG_DATA_OEM_SIZE);
}

void asf_msg_data_unpack_supported_entities(uint8_t *d, struct asf_data *a)
{
	a->supported_entities = unpackr(&(d)[ASF_MSG_DATA_SUP_ENT_OFFSET], ASF_MSG_DATA_SUP_ENT_SIZE);
}

void asf_msg_data_unpack_supported_interactions(uint8_t *d, struct asf_data *a)
{
	a->supported_interactions = unpackr(&(d)[ASF_MSG_DATA_SUP_INT_OFFSET], ASF_MSG_DATA_SUP_INT_SIZE);
}

uint32_t asf_msg_header_get_iana(struct asf_header *a)
{
	return a->iana_number;
}

uint8_t asf_msg_header_get_length(struct asf_header *a)
{
	return a->data_length;
}

uint8_t asf_msg_header_get_reserved(struct asf_header *a)
{
	return a->reserved;
}

uint8_t asf_msg_header_get_tag(struct asf_header *a)
{
	return a->tag;
}

uint8_t asf_msg_header_get_type(struct asf_header *a)
{
	return a->type;
}

void asf_msg_header_set_iana(struct asf_header *a)
{
	a->iana_number = 4542;
}

void asf_msg_header_set_length(struct asf_header *a, uint8_t i)
{
	a->data_length = i;
}

void asf_msg_header_set_reserved(struct asf_header *a)
{
	a->reserved = 0;
}

void asf_msg_header_set_tag(struct asf_header *a, uint8_t i)
{
	a->tag = i;
}

void asf_msg_header_set_type(struct asf_header *a, uint8_t i)
{
	a->type = i;
}

void asf_msg_header_pack_iana(uint8_t *d, struct asf_header *a)
{
	packr(&(d)[ASF_MSG_HEADER_IANA_OFFSET], a->iana_number, ASF_MSG_HEADER_IANA_SIZE);
}

void asf_msg_header_pack_type(uint8_t *d, struct asf_header *a)
{
	packr(&(d)[ASF_MSG_HEADER_TYPE_OFFSET], a->type, ASF_MSG_HEADER_TYPE_SIZE);
}

void asf_msg_header_pack_tag(uint8_t *d, struct asf_header *a)
{
	packr(&(d)[ASF_MSG_HEADER_TAG_OFFSET], a->tag, ASF_MSG_HEADER_TAG_SIZE);
}

void asf_msg_header_pack_reserved(uint8_t *d, struct asf_header *a)
{
	packr(&(d)[ASF_MSG_HEADER_RESERVED_OFFSET], a->reserved, ASF_MSG_HEADER_RESERVED_SIZE);
}

void asf_msg_header_pack_data_length(uint8_t *d, struct asf_header *a)
{
	packr(&(d)[ASF_MSG_HEADER_DATA_LEN_OFFSET], a->data_length, ASF_MSG_HEADER_DATA_LEN_SIZE);
}

void asf_msg_header_unpack_iana(uint8_t *d, struct asf_header *a)
{
	a->iana_number = unpackr(&(d)[ASF_MSG_HEADER_IANA_OFFSET], ASF_MSG_HEADER_IANA_SIZE);
}

void asf_msg_header_unpack_type(uint8_t *d, struct asf_header *a)
{
	a->type = unpackr(&(d)[ASF_MSG_HEADER_TYPE_OFFSET], ASF_MSG_HEADER_TYPE_SIZE);
}

void asf_msg_header_unpack_tag(uint8_t *d, struct asf_header *a)
{
	a->tag = unpackr(&(d)[ASF_MSG_HEADER_TAG_OFFSET], ASF_MSG_HEADER_TAG_SIZE);
}

void asf_msg_header_unpack_reserved(uint8_t *d, struct asf_header *a)
{
	a->reserved = unpackr(&(d)[ASF_MSG_HEADER_RESERVED_OFFSET], ASF_MSG_HEADER_RESERVED_SIZE);
}

void asf_msg_header_unpack_data_length(uint8_t *d, struct asf_header *a)
{
	a->data_length = unpackr(&(d)[ASF_MSG_HEADER_DATA_LEN_OFFSET], ASF_MSG_HEADER_DATA_LEN_SIZE);
}

uint8_t rmcp_msg_header_get_class_tag(struct rmcp_header *r)
{
	return r->message_class & 0x0f;
}

uint8_t rmcp_msg_header_get_class_ack(struct rmcp_header *r)
{
	return r->message_class >> 7;
}

uint8_t rmcp_msg_header_get_reserved(struct rmcp_header *r)
{
	return r->reserved;
}

uint8_t rmcp_msg_header_get_sequence(struct rmcp_header *r)
{
	return r->sequence_number;
}

uint8_t rmcp_msg_header_get_version(struct rmcp_header *r)
{
	return r->version;
}
void rmcp_msg_header_set_version(struct rmcp_header *r)
{
	r->version = 0x06;
}

void rmcp_msg_header_set_reserved(struct rmcp_header *r)
{
	r->reserved = 0x00;
}

void rmcp_msg_header_set_sequence(struct rmcp_header *r, uint8_t i)
{
	r->sequence_number = i;
}

void rmcp_msg_header_set_class_type(struct rmcp_header *r, uint8_t i)
{
	/*
	* 1 bit, high bit
	* set the type of a message
	*/

	r->message_class &= 127;
	r->message_class |= i << 7;
}

void rmcp_msg_header_set_class_tag(struct rmcp_header *r, uint8_t i)
{
	/*
	* set the class of a message 4 bits, low bits
	* preserve the ACK/normal 1 bit, high bit
	*/
	r->message_class &= 1 << 7;
	r->message_class |= i;
}

void rmcp_msg_header_pack_version(uint8_t *d, struct rmcp_header *r)
{
	packr(&(d)[RMCP_MSG_HEADER_VERSION_OFFSET], r->version, RMCP_MSG_HEADER_VERSION_SIZE);
}

void rmcp_msg_header_pack_reserved(uint8_t *d, struct rmcp_header *r)
{
	packr(&(d)[RMCP_MSG_HEADER_RESERVED_OFFSET], r->reserved, RMCP_MSG_HEADER_RESERVED_SIZE);
}

void rmcp_msg_header_pack_sequence_number(uint8_t *d, struct rmcp_header *r)
{
	packr(&(d)[RMCP_MSG_HEADER_SEQUENCE_OFFSET], r->sequence_number, RMCP_MSG_HEADER_SEQUENCE_SIZE);
}

void rmcp_msg_header_pack_message_class(uint8_t *d, struct rmcp_header *r)
{
	packr(&(d)[RMCP_MSG_HEADER_CLASS_OFFSET], r->message_class, RMCP_MSG_HEADER_CLASS_SIZE);
}

void rmcp_msg_header_unpack_version(uint8_t *d, struct rmcp_header *r)
{
	r->version = unpackr(&(d)[RMCP_MSG_HEADER_VERSION_OFFSET], RMCP_MSG_HEADER_VERSION_SIZE);
}

void rmcp_msg_header_unpack_reserved(uint8_t *d, struct rmcp_header *r)
{
	r->reserved = unpackr(&(d)[RMCP_MSG_HEADER_RESERVED_OFFSET], RMCP_MSG_HEADER_RESERVED_SIZE);
}

void rmcp_msg_header_unpack_sequence_number(uint8_t *d, struct rmcp_header *r)
{
	r->sequence_number = unpackr(&(d)[RMCP_MSG_HEADER_SEQUENCE_OFFSET], RMCP_MSG_HEADER_SEQUENCE_SIZE);
}

void rmcp_msg_header_unpack_message_class(uint8_t *d, struct rmcp_header *r)
{
	r->message_class = unpackr(&(d)[RMCP_MSG_HEADER_CLASS_OFFSET], RMCP_MSG_HEADER_CLASS_SIZE);
}

uint8_t rmcp_session_get_message_tag(struct rmcp_session *r)
{
	return r->message_tag;
}

uint8_t rmcp_session_get_privilege_level_reserved(struct rmcp_session *r)
{
	return (r->max_privilege_level & 240) >> 4;
}

uint8_t rmcp_session_get_privilege_level_request(struct rmcp_session *r)
{
	return r->max_privilege_level & 16;
}

uint32_t rmcp_session_get_session_id(struct rmcp_session *r)
{
	return r->session_id;
}

uint8_t rmcp_session_get_authentication_payload_type(struct rmcp_session *r)
{
	/*
	* (2^64-1)-(2^56-1)
	*/
	return (r->authentication_payload & 18374686479671623680LU) >> 56;
}

uint16_t rmcp_session_get_authenticaion_payload_reserved23(struct rmcp_session *r)
{
	/*
	* (2^56-1)-(2^40-1)
	*/
	return (r->authentication_payload & 72056494526300160LU >> 40);
}
uint8_t rmcp_session_get_authentication_payload_length(struct rmcp_session *r)
{
	/*
	* (2^40-1)-(2^32-1)
	*/
	return (r->authentication_payload & 1095216660480) >> 32;
}

uint8_t rmcp_session_get_authenticaiton_payload_algorithm(struct rmcp_session *r)
{
	/*
	* (2^32-1)-(2^24-1)
	*/
	return (r->authentication_payload & 4278190080) >> 24;
}

uint32_t rmcp_session_get_authentication_payload_reserved_678(struct rmcp_session *r)
{
	/*
	* 2^24-1
	*/
	return r->authentication_payload & 16777215;
}

uint8_t rmcp_session_get_confidentiality_payload_type(struct rmcp_session *r)
{
	/*
	* (2^64-1)-(2^56-1)
	*/
	return (r->confidentiality_payload & 18374686479671623680LU) >> 56;
}

uint16_t rmcp_session_get_confidentiality_payload_reserved23(struct rmcp_session *r)
{
	/*
	* (2^56-1)-(2^40-1)
	*/
	return (r->confidentiality_payload & 72056494526300160LU >> 40);
}
uint8_t rmcp_session_get_confidentiality_payload_length(struct rmcp_session *r)
{
	/*
	* (2^40-1)-(2^32-1)
	*/
	return (r->confidentiality_payload & 1095216660480) >> 32;
}

uint8_t rmcp_session_get_confidentiality_payload_algorithm(struct rmcp_session *r)
{
	/*
	* (2^32-1)-(2^24-1)
	*/
	return (r->confidentiality_payload & 4278190080) >> 24;
}

uint32_t rmcp_session_get_confidentiality_payload_reserved_678(struct rmcp_session *r)
{
	/*
	* 2^24-1
	*/
	return r->confidentiality_payload & 16777215;
}

void rmcp_session_set_message_tag(struct rmcp_session *r, uint8_t i)
{
	r->message_tag = i;
}

void rmcp_session_set_privilege_level_reserved(struct rmcp_session *r)
{
	r->max_privilege_level &= 15;
}

void rmcp_session_set_privilege_level_request(struct rmcp_session *r, uint8_t i)
{
	r->max_privilege_level |= i & 16;
}

void rmcp_session_set_reserved(struct rmcp_session *r, uint8_t i)
{
	r->reserved = i;
}

void rmcp_session_set_session_id(struct rmcp_session *r, uint32_t i)
{
	r->session_id = i;
}

void rmcp_session_set_authentication_payload_type(struct rmcp_session *r, uint8_t i)
{
	/*
	* authentication algorithm = 00h
	*/

	// 2^64-1
	r->authentication_payload &= 9223372036854775807;
	r->authentication_payload |= (uint64_t)i << 56;
}

void rmcp_session_set_authentication_payload_reserved23(struct rmcp_session *r, uint16_t i)
{
	/*
	*  reserved = 00h
	*/
	// (2^64-1)-(2^56-1)+(2^40-1)
	r->authentication_payload &= 9187343789591625727;
	// r->authentication_payload |= (uint64_t)i << 48;
}

void rmcp_session_set_authentication_payload_length(struct rmcp_session *r, uint8_t i)
{
	/*
	* total length of the payload including this header
	* 08h for this spec
	*/
	// (2^64-1)-(2^40-1)+(2^32-1)
	r->authentication_payload &= 9223371489246445567;
	r->authentication_payload |= (uint64_t)i << 40;
}

void rmcp_session_set_authentication_payload_algorithm(struct rmcp_session *r, uint8_t i)
{
	// (2^64-1)-(2^32-1)+(2^24-1)
	r->authentication_payload &= 9223372034715680767;
	r->authentication_payload |= (uint64_t)i << 32;
}

void rmcp_session_set_authenticaiton_payload_reserved_678(struct rmcp_session *r, uint32_t i)
{
	/*
	* reserved bytes 6-8
	* (2^64-1)-(2^24-1)
	*/
	r->authentication_payload &= 18446744073692774400LU;
	// 2^24-1
	// r->integrity_payload |= (i & 16777215);
};

void rmcp_session_set_integrity_payload_type(struct rmcp_session *r, uint8_t i)
{
	/*
	* 01h = integrity algorithm
	* (2^56-1)
	*/
	r->integrity_payload &= 72057594037927935LU;
	r->integrity_payload |= (uint64_t)i << 56;
}

void rmcp_session_set_integrity_payload_reserved_23(struct rmcp_session *r, uint16_t i)
{
	/*
	* reserved bytes 2-3
	* set to 0000h
	*
	* (2^64-1)-(2^56-1)+(2^40-1)
	*/

	r->integrity_payload &= 18374687579183251455LU;
	// r->integrity_payload |= (uint64_t)i << 40;
}

void rmcp_session_set_integrity_payload_length(struct rmcp_session *r, uint8_t i)
{
	/*
	*  length in bytes of the payload including the header
	*
	* (2^64-1)-(2^40-1)+(2^32-1)
	*/
	r->integrity_payload &= 18446742978492891135LU;
	r->integrity_payload |= (uint64_t)i << 32;
}

void rmcp_session_set_integrity_payload_algorithm(struct rmcp_session *r, uint8_t i)
{
	/*
	*
	*
	* bits 6-7 reserved
	* bits 0-5 integrity algorithm
	*
	* (2^64-1)-(2^32-1)+(2^24-1)
	*/
	r->integrity_payload &= 18446744069431361535LU;
	r->integrity_payload |= (uint64_t)(i & 31) << 24;
}

void rmcp_session_set_integrity_payload_reserved_678(struct rmcp_session *r, uint32_t i)
{
	/*
	* reserved bytes 6-8
	* (2^64-1)-(2^24-1)
	*/
	r->integrity_payload &= 18446744073692774400LU;
	// 2^24-1
	// r->integrity_payload |= (i & 16777215);
};

void rmcp_session_set_confidentiality_payload_type(struct rmcp_session *r, uint8_t i)
{
	/*
	* 01h = confidentiality algorithm
	* (2^56-1)
	*/
	r->confidentiality_payload &= 72057594037927935LU;
	r->confidentiality_payload |= (uint64_t)i << 56;
}

void rmcp_session_set_confidentiality_payload_reserved_23(struct rmcp_session *r, uint16_t i)
{
	/*
	* reserved bytes 2-3
	* set to 0000h
	*
	* (2^64-1)-(2^56-1)+(2^40-1)
	*/

	r->confidentiality_payload &= 18374687579183251455LU;
	// r->confidentiality_payload |= (uint64_t)i << 40;
}

void rmcp_session_set_confidentiality_payload_length(struct rmcp_session *r, uint8_t i)
{
	/*
	*  length in bytes of the payload including the header
	*
	* (2^64-1)-(2^40-1)+(2^32-1)
	*/
	r->confidentiality_payload &= 18446742978492891135LU;
	r->confidentiality_payload |= (uint64_t)i << 32;
}

void rmcp_session_set_confidentiality_payload_algorithm(struct rmcp_session *r, uint8_t i)
{
	/*
	*
	*
	* bits 6-7 reserved
	* bits 0-5 confidentiality algorithm
	*
	* (2^64-1)-(2^32-1)+(2^24-1)
	*/
	r->confidentiality_payload &= 18446744069431361535LU;
	r->confidentiality_payload |= (uint64_t)(i & 31) << 24;
}

void rmcp_session_set_confidentiality_payload_reserved_678(struct rmcp_session *r, uint32_t i)
{
	/*
	* reserved bytes 6-8
	* (2^64-1)-(2^24-1)
	*/
	r->confidentiality_payload &= 18446744073692774400LU;
	// 2^24-1
	// r->confidentiality_payload |= (i & 16777215);
};

void rmcp_ping_set()
{
	struct rmcp_header r;
	r.message_class = 0;
	r.version = 0;
	rmcp_msg_header_set_version(&r);
	rmcp_msg_header_set_reserved(&r);
	rmcp_msg_header_set_sequence(&r, 0);
	rmcp_msg_header_set_class_type(&r, 0);
	rmcp_msg_header_set_class_tag(&r, 6);
}
