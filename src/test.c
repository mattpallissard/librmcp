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
#include <assert.h>
#include <log.h>
#include <rmcp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void t_asf_msg_data_get_iana()
{
	struct asf_data a;
	uint32_t i;
	printu(LOG_DEBUG, __func__);

	asf_msg_data_set_iana(&a, 4542);
	i = asf_msg_data_get_iana(&a);

	printu(LOG_DEBUG, "\t\tassert(%X == %X)", 4542, i);
	assert(4542 == i);
}
void t_asf_msg_data_get_oem()
{
	struct asf_data a;
	uint32_t i;
	printu(LOG_DEBUG, __func__);

	asf_msg_data_set_oem(&a, 4542);
	i = asf_msg_data_get_oem(&a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 4542, i);
	assert(4542 == i);
}

void t_asf_msg_data_get_supported_entities_ipmi()
{
	struct asf_data a;
	uint8_t i;
	printu(LOG_DEBUG, __func__);

	asf_msg_data_set_supported_entities_ipmi(&a, 1);
	i = asf_msg_data_get_supported_entities_ipmi(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 1, i);

	asf_msg_data_set_supported_entities_ipmi(&a, 0);
	i = asf_msg_data_get_supported_entities_ipmi(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 0, i);
	assert(0 == i);
}
void t_asf_msg_data_get_supported_entities_version()
{
	struct asf_data a;
	uint8_t i;
	printu(LOG_DEBUG, __func__);

	a.supported_entities = ~0xf;
	asf_msg_data_set_supported_entities_version(&a);
	i = asf_msg_data_get_supported_entities_version(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 1, i);
	assert(1 == i);
}
void t_asf_msg_data_get_supported_interactions_security()
{
	struct asf_data a;
	uint8_t i, j = 1;
	printu(LOG_DEBUG, __func__);

	do {
		asf_msg_data_set_supported_interactions_security(&a, j);
		i = asf_msg_data_get_supported_interactions_security(&a);
		printu(LOG_DEBUG, "\t\tassert(%u == %u)", j, i);
	} while (j--);
}

void t_asf_msg_data_get_supported_interactions_dash()
{
	struct asf_data a;
	uint8_t i;
	printu(LOG_DEBUG, __func__);

	asf_msg_data_set_supported_interactions_dash(&a, 1);
	i = asf_msg_data_get_supported_interactions_dash(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 1, i);
	assert(1 == i);

	asf_msg_data_set_supported_interactions_dash(&a, 0);
	i = asf_msg_data_get_supported_interactions_dash(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 0, i);
	assert(0 == i);
}
void t_asf_msg_data_set_iana()
{
	struct asf_data a;
	uint32_t i = 4294967295;
	printu(LOG_DEBUG, __func__);
	asf_msg_data_set_iana(&a, i);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.iana_number, i);
	assert(a.iana_number == i);
}

void t_asf_msg_data_set_oem()
{
	struct asf_data a;
	uint32_t i = 4294967295;
	printu(LOG_DEBUG, __func__);
	asf_msg_data_set_oem(&a, i);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.oem_defined, i);
	assert(a.oem_defined == i);
}

void t_asf_msg_data_set_supported_entities_ipmi()
{
	struct asf_data a;
	uint8_t i;
	printu(LOG_DEBUG, __func__);
	a.supported_entities = 65;
	asf_msg_data_set_supported_entities_ipmi(&a, 1);

	i = a.supported_entities >> 7;

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 193, a.supported_entities);
	assert(193 == a.supported_entities);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 1, i);
	assert(1 == i);

	asf_msg_data_set_supported_entities_ipmi(&a, 0);
	i = a.supported_entities >> 7;

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 0, i);
	assert(0 == i);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 65, a.supported_entities);
	assert(65 == a.supported_entities);
}

void t_asf_msg_data_set_supported_entities_version()
{
	struct asf_data a;
	uint8_t i;
	printu(LOG_DEBUG, __func__);
	a.supported_entities = 65;
	asf_msg_data_set_supported_entities_ipmi(&a, 1);

	i = a.supported_entities >> 7;

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 193, a.supported_entities);
	assert(193 == a.supported_entities);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 1, i);
	assert(1 == i);

	asf_msg_data_set_supported_entities_ipmi(&a, 0);
	i = a.supported_entities >> 7;

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 0, i);
	assert(0 == i);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 65, a.supported_entities);
	assert(65 == a.supported_entities);
}

void t_asf_msg_data_set_supported_interactions_security()
{
	struct asf_data a;
	printu(LOG_DEBUG, __func__);

	a.supported_interactions = 255;
	asf_msg_data_set_supported_interactions_security(&a, 0);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 255, a.supported_interactions);
	assert(127 == a.supported_interactions);

	asf_msg_data_set_supported_interactions_security(&a, 1);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 255, a.supported_interactions);
	assert(255 == a.supported_interactions);
}

void t_asf_msg_data_set_supported_interactions_dash()
{
	struct asf_data a;
	printu(LOG_DEBUG, __func__);

	a.supported_interactions = 255;
	asf_msg_data_set_supported_interactions_dash(&a, 0);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 223, a.supported_interactions);
	assert(223 == a.supported_interactions);

	asf_msg_data_set_supported_interactions_dash(&a, 1);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 255, a.supported_interactions);
	assert(255 == a.supported_interactions);
}

void t_asf_msg_data_set_supported_interactions_reserved()
{
	struct asf_data a;
	printu(LOG_DEBUG, __func__);

	a.supported_interactions = 255;
	asf_msg_data_set_supported_interactions_reserved(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", 160, a.supported_interactions);
	assert(160 == a.supported_interactions);
}

void t_asf_msg_data_pack_iana()
{
	struct asf_data a;
	uint8_t d[16];
	uint32_t i;

	memset(d, '\0', 16);
	a.iana_number = 4294967295;

	printu(LOG_DEBUG, __func__);
	asf_msg_data_pack_iana(d, &a);
	i = unpackl(&(d)[ASF_MSG_DATA_IANA_OFFSET], ASF_MSG_DATA_IANA_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.iana_number);
	assert(i == a.iana_number);
}

void t_asf_msg_data_pack_oem()
{
	struct asf_data a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.oem_defined = 4294967295;

	printu(LOG_DEBUG, __func__);
	asf_msg_data_pack_oem(d, &a);
	i = unpackl(&(d)[ASF_MSG_DATA_OEM_OFFSET], ASF_MSG_DATA_OEM_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.oem_defined);
	assert(i == a.oem_defined);
}

void t_asf_msg_data_pack_supported_entities()
{
	struct asf_data a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.supported_entities = 255;

	printu(LOG_DEBUG, __func__);
	asf_msg_data_pack_supported_entities(d, &a);
	i = unpackl(&(d)[ASF_MSG_DATA_SUP_ENT_OFFSET], ASF_MSG_DATA_SUP_ENT_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.supported_entities);
	assert(i == a.supported_entities);
}

void t_asf_msg_data_pack_supported_interactions()
{
	struct asf_data a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.supported_interactions = 255;

	printu(LOG_DEBUG, __func__);
	asf_msg_data_pack_supported_interactions(d, &a);
	i = unpackl(&(d)[ASF_MSG_DATA_SUP_INT_OFFSET], ASF_MSG_DATA_SUP_INT_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.supported_interactions);
	assert(i == a.supported_interactions);
}
void t_asf_msg_data_unpack_iana()
{
	/*
	* 4 bytes
	*/
	printu(LOG_DEBUG, __func__);
	struct asf_data a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i = 34480385;

	a.iana_number = i;
	memset(d, '\0', ASF_MSG_LONGEST);

	asf_msg_data_pack_iana(d, &a);
	a.iana_number = 0;

	asf_msg_data_unpack_iana(d, &a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.iana_number, i);
	assert(a.iana_number == i);
}

void t_asf_msg_data_unpack_oem()
{
	/*
	* 4 bytes
	*/
	printu(LOG_DEBUG, __func__);
	struct asf_data a;
	uint8_t d[ASF_MSG_LONGEST];
	uint64_t i = 67305985;
	a.oem_defined = i;

	memset(d, '\0', ASF_MSG_LONGEST);

	asf_msg_data_pack_oem(d, &a);
	a.oem_defined = 0;

	asf_msg_data_unpack_oem(d, &a);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", a.oem_defined, i);
	assert(a.oem_defined == i);
}

void t_asf_msg_data_unpack_supported_entities()
{
	/*
	* 1 byte
	*/
	struct asf_data a;
	uint8_t d[ASF_MSG_LONGEST];
	d[ASF_MSG_DATA_SUP_ENT_OFFSET] = 4;
	printu(LOG_DEBUG, __func__);

	asf_msg_data_unpack_supported_entities(d, &a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.supported_entities, 4);
	assert(a.supported_entities == 4);
}

void t_asf_msg_header_get_iana()
{
	uint64_t i;
	struct asf_header a;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_set_iana(&a);
	i = asf_msg_header_get_iana(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 4542);
	assert(i == 4542);
}

void t_asf_msg_header_get_length()
{
	uint8_t i;
	struct asf_header a;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_set_length(&a, 255);
	i = asf_msg_header_get_length(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 255);
	assert(i == 255);
}

void t_asf_msg_header_get_reserved()
{
	uint8_t i;
	struct asf_header a;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_set_reserved(&a);
	i = asf_msg_header_get_reserved(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_asf_msg_header_get_tag()
{
	uint8_t i;
	struct asf_header a;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_set_tag(&a, 255);
	i = asf_msg_header_get_tag(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 255);
	assert(i == 255);
}
void t_asf_msg_header_get_type()
{
	uint8_t i;
	struct asf_header a;
	printu(LOG_DEBUG, __func__);

	asf_msg_header_set_type(&a, 40);
	i = asf_msg_header_get_type(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 40);
	assert(i == 40);
}

void t_asf_msg_header_pack_iana()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.iana_number = 4294967295;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_pack_iana(d, &a);
	i = unpackl(&(d)[ASF_MSG_HEADER_IANA_OFFSET], ASF_MSG_HEADER_IANA_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.iana_number);
	assert(i == a.iana_number);
}

void t_asf_msg_header_pack_type()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.type = 255;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_pack_type(d, &a);
	i = unpackl(&(d)[ASF_MSG_HEADER_TYPE_OFFSET], ASF_MSG_HEADER_TYPE_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.type);
	assert(i == a.type);
}

void t_asf_msg_header_pack_tag()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.tag = 255;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_pack_tag(d, &a);
	i = unpackl(&(d)[ASF_MSG_HEADER_TAG_OFFSET], ASF_MSG_HEADER_TAG_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.type);
	assert(i == a.type);
}

void t_asf_msg_header_pack_data_length()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.data_length = 255;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_pack_data_length(d, &a);
	i = unpackl(&(d)[ASF_MSG_HEADER_DATA_LEN_OFFSET], ASF_MSG_HEADER_DATA_LEN_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.data_length);
	assert(i == a.data_length);
}

void t_asf_msg_header_pack_reserved()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i;

	memset(d, '\0', ASF_MSG_LONGEST);
	a.reserved = 255;

	printu(LOG_DEBUG, __func__);
	asf_msg_header_pack_reserved(d, &a);
	i = unpackl(&(d)[ASF_MSG_HEADER_RESERVED_OFFSET], ASF_MSG_HEADER_RESERVED_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, a.reserved);
	assert(i == a.reserved);
}

void t_asf_msg_header_unpack_iana()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint32_t i = 4294967295;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	a.iana_number = i;
	asf_msg_header_pack_iana(d, &a);

	a.iana_number = 0;
	asf_msg_header_unpack_iana(d, &a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.iana_number, i);
	assert(a.iana_number == i);
}

void t_asf_msg_header_unpack_type()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	a.type = i;
	asf_msg_header_pack_type(d, &a);

	a.type = 0;
	asf_msg_header_unpack_type(d, &a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.type, i);
	assert(a.type == i);
}

void t_asf_msg_header_unpack_tag()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	a.tag = i;
	asf_msg_header_pack_tag(d, &a);

	a.tag = 0;
	asf_msg_header_unpack_tag(d, &a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.tag, i);
	assert(a.tag == i);
}

void t_asf_msg_header_unpack_reserved()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	a.reserved = i;
	asf_msg_header_pack_reserved(d, &a);

	a.reserved = 0;
	asf_msg_header_unpack_reserved(d, &a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.reserved, i);
	assert(a.reserved == i);
}

void t_asf_msg_header_unpack_data_length()
{
	struct asf_header a;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	a.data_length = i;
	asf_msg_header_pack_data_length(d, &a);

	a.data_length = 0;
	asf_msg_header_unpack_data_length(d, &a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.data_length, i);
	assert(a.data_length == i);
}

void t_asf_msg_header_set_iana()
{
	struct asf_header a;
	printu(LOG_DEBUG, __func__);
	asf_msg_header_set_iana(&a);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.iana_number, 4542);
	assert(a.iana_number == 4542);
}

void t_asf_msg_header_set_length()
{
	/*
	* 1 byte
	*/
	struct asf_header a;
	printu(LOG_DEBUG, __func__);

	asf_msg_header_set_length(&a, 255);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.data_length, 255);
	assert(a.data_length == 255);
}

void t_asf_msg_header_set_reserved()
{
	/*
	* 1 byte, 4542 is iana
	*/
	struct asf_header a;
	printu(LOG_DEBUG, __func__);

	asf_msg_header_set_reserved(&a);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.reserved, 0);
	assert(a.reserved == 0);
}

void t_asf_msg_header_set_tag()
{
	/*
	* 1 byte, 0-254 RMCP request/response messages,
	* 255 = the message is unidirectional and not part of a request/response pair
	*/
	struct asf_header a;
	printu(LOG_DEBUG, __func__);

	asf_msg_header_set_tag(&a, 255);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.tag, 255);
	assert(a.tag == 255);
}

void t_asf_msg_header_set_type()
{
	/*
	* 1 byte, 80 == 'ping', 40 == 'pong'
	*/
	struct asf_header a;
	printu(LOG_DEBUG, __func__);

	asf_msg_header_set_type(&a, 40);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", a.type, 40);
	assert(a.type == 40);
}

void t_rmcp_msg_header_get_class_tag()
{
	int i;
	struct rmcp_header r;
	r.message_class = 134;
	printu(LOG_DEBUG, __func__);

	i = rmcp_msg_header_get_class_tag(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 6);
	assert(i == 6);
}

void t_rmcp_msg_header_get_class_ack()
{
	int i;
	struct rmcp_header r;

	printu(LOG_DEBUG, __func__);

	r.message_class = 64;
	i = rmcp_msg_header_get_class_ack(&r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);

	r.message_class = 128;
	i = rmcp_msg_header_get_class_ack(&r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 1);
	assert(i == 1);
}

void t_rmcp_msg_header_get_reserved()
{
	int i;
	struct rmcp_header r;

	printu(LOG_DEBUG, __func__);
	rmcp_msg_header_set_reserved(&r);
	i = rmcp_msg_header_get_reserved(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_msg_header_get_sequence()
{
	int i;
	struct rmcp_header r;
	r.sequence_number = 1;
	printu(LOG_DEBUG, __func__);

	i = rmcp_msg_header_get_sequence(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 1);
	assert(i == 1);
}

void t_rmcp_msg_header_get_version()
{
	int i;
	struct rmcp_header r;

	printu(LOG_DEBUG, __func__);
	rmcp_msg_header_set_version(&r);
	i = rmcp_msg_header_get_version(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 6);
	assert(i == 6);
}

void t_rmcp_msg_header_pack_version()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i;

	printu(LOG_DEBUG, __func__);

	memset(d, 1, ASF_MSG_LONGEST);
	r.version = 0;

	rmcp_msg_header_pack_version(d, &r);
	i = unpackl(&(d)[RMCP_MSG_HEADER_VERSION_OFFSET], RMCP_MSG_HEADER_VERSION_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, r.version);
	assert(i == r.version);
}

void t_rmcp_msg_header_pack_reserved()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i;

	printu(LOG_DEBUG, __func__);

	memset(d, 1, ASF_MSG_LONGEST);
	r.reserved = 255;

	rmcp_msg_header_pack_reserved(d, &r);
	i = unpackl(&(d)[RMCP_MSG_HEADER_RESERVED_OFFSET], RMCP_MSG_HEADER_RESERVED_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, r.reserved);
	assert(i == r.reserved);
}

void t_rmcp_msg_header_pack_sequence_number()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i;

	printu(LOG_DEBUG, __func__);

	memset(d, 0, ASF_MSG_LONGEST);
	r.sequence_number = 255;

	rmcp_msg_header_pack_sequence_number(d, &r);
	i = unpackl(&(d)[RMCP_MSG_HEADER_SEQUENCE_OFFSET], RMCP_MSG_HEADER_SEQUENCE_SIZE);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, r.sequence_number);
	assert(i == r.sequence_number);
}

void t_rmcp_msg_header_pack_message_class()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, 1, ASF_MSG_LONGEST);
	r.message_class = i;

	rmcp_msg_header_pack_message_class(d, &r);
	r.message_class = 0;
	rmcp_msg_header_unpack_message_class(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, r.message_class);
	assert(i == r.message_class);
}

void t_rmcp_msg_header_unpack_version()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	r.version = i;
	rmcp_msg_header_pack_version(d, &r);

	r.version = 0;
	rmcp_msg_header_unpack_version(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.version, i);
	assert(r.version == i);
}

void t_rmcp_msg_header_unpack_reserved()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	r.reserved = i;
	rmcp_msg_header_pack_reserved(d, &r);

	r.reserved = 0;
	rmcp_msg_header_unpack_reserved(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.reserved, i);
	assert(r.reserved == i);
}
void t_rmcp_msg_header_unpack_sequence_number()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	r.sequence_number = i;
	rmcp_msg_header_pack_sequence_number(d, &r);

	r.sequence_number = 0;
	rmcp_msg_header_unpack_sequence_number(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.sequence_number, i);
	assert(r.sequence_number == i);
}
void t_rmcp_msg_header_unpack_message_class()
{
	struct rmcp_header r;
	uint8_t d[ASF_MSG_LONGEST];
	uint8_t i = 255;

	printu(LOG_DEBUG, __func__);

	memset(d, '\0', ASF_MSG_LONGEST);
	r.message_class = i;
	rmcp_msg_header_pack_message_class(d, &r);

	r.message_class = 0;
	rmcp_msg_header_unpack_message_class(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_class, i);
	assert(r.message_class == i);
}
void t_rmcp_msg_header_set_sequence()
{
	/*
	* 1 byte
	*/
	struct rmcp_header r;
	printu(LOG_DEBUG, __func__);
	r.sequence_number = 1;
	rmcp_msg_header_set_sequence(&r, 2);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.sequence_number, 2);
	assert(r.sequence_number == 2);
}

void t_rmcp_msg_header_set_version()
{
	/*
	* 1 byte
	* 06h = RMCP Version 1.0
	*/
	struct rmcp_header r;
	printu(LOG_DEBUG, __func__);
	rmcp_msg_header_set_version(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.version, 6);
	assert(r.version == 6);
}

void t_rmcp_msg_header_set_reserved()
{
	/*
	* 1 byte
	* 00h == reserved
	*/
	struct rmcp_header r;
	printu(LOG_DEBUG, __func__);
	rmcp_msg_header_set_reserved(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.reserved, 0);
}

void t_rmcp_msg_header_set_class_tag()
{
	/*
	* 1 bit, high bit
	*/
	struct rmcp_header r;
	r.message_class = 0;
	printu(LOG_DEBUG, __func__);

	rmcp_msg_header_set_class_type(&r, 1);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_class, 128);
	assert(r.message_class == 128);

	rmcp_msg_header_set_class_tag(&r, 6);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_class, 134);
	assert(r.message_class == 134);
}

void t_rmcp_msg_header_set_class_type()
{
	/*
	* 1 bit, high bit
	*/
	struct rmcp_header r;
	r.message_class = 64;
	printu(LOG_DEBUG, __func__);

	rmcp_msg_header_set_class_type(&r, 1);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_class, 192);
	assert(r.message_class == 192);

	rmcp_msg_header_set_class_type(&r, 0);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_class, 64);
	assert(r.message_class == 64);
}

void t_rmcp_session_get_message_tag()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.message_tag = 0;

	rmcp_session_set_message_tag(&r, 255);
	i = rmcp_session_get_message_tag(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 255);
	assert(i == 255);
}

void t_rmcp_session_get_privilege_level_reserved()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.max_privilege_level = 0;

	rmcp_session_set_privilege_level_reserved(&r);
	i = rmcp_session_get_privilege_level_reserved(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_privilege_level_request()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.max_privilege_level = 0;

	rmcp_session_set_privilege_level_request(&r, 63);
	i = rmcp_session_get_privilege_level_request(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_session_id()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.session_id = 0;

	rmcp_session_set_session_id(&r, 255);
	i = rmcp_session_get_session_id(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 255);
	assert(i == 255);
}

void t_rmcp_session_get_authentication_payload_type()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.authentication_payload = 0;

	rmcp_session_set_authentication_payload_type(&r, 63);
	i = rmcp_session_get_authentication_payload_type(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 63);
	assert(i == 63);
}

void t_rmcp_session_get_authentication_payload_reserved_23()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.authentication_payload = 0;

	rmcp_session_set_authentication_payload_reserved_23(&r, 63);
	i = rmcp_session_get_authentication_payload_reserved_23(&r);
	// should always set zero
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_authentication_payload_length()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.authentication_payload = 0;

	rmcp_session_set_authentication_payload_length(&r, 63);
	i = rmcp_session_get_authentication_payload_length(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 63);
	assert(i == 63);
}

void t_rmcp_session_get_authentication_payload_algorithm()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.authentication_payload = 0;

	rmcp_session_set_authentication_payload_algorithm(&r, 12);
	i = rmcp_session_get_authentication_payload_algorithm(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 12);
	assert(i == 12);
}

void t_rmcp_session_get_authentication_payload_reserved_678()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.authentication_payload = 0;

	rmcp_session_set_authentication_payload_reserved_678(&r, 63);
	i = rmcp_session_get_authentication_payload_reserved_678(&r);
	// should always set zero
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_integrity_payload_type()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.integrity_payload = 0;

	rmcp_session_set_integrity_payload_type(&r, 63);
	i = rmcp_session_get_integrity_payload_type(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 63);
	assert(i == 63);
}

void t_rmcp_session_get_integrity_payload_reserved_23()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.integrity_payload = 0;

	rmcp_session_set_integrity_payload_reserved_23(&r, 63);
	i = rmcp_session_get_integrity_payload_reserved_23(&r);
	// should always set zero
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_integrity_payload_length()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.integrity_payload = 0;

	rmcp_session_set_integrity_payload_length(&r, 63);
	i = rmcp_session_get_integrity_payload_length(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 63);
	assert(i == 63);
}

void t_rmcp_session_get_integrity_payload_algorithm()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.integrity_payload = 0;

	rmcp_session_set_integrity_payload_algorithm(&r, 12);
	i = rmcp_session_get_integrity_payload_algorithm(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 12);
	assert(i == 12);
}

void t_rmcp_session_get_integrity_payload_reserved_678()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.integrity_payload = 0;

	rmcp_session_set_integrity_payload_reserved_678(&r, 63);
	i = rmcp_session_get_integrity_payload_reserved_678(&r);
	// should always set zero
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_confidentiality_payload_type()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.confidentiality_payload = 0;

	rmcp_session_set_confidentiality_payload_type(&r, 63);
	i = rmcp_session_get_confidentiality_payload_type(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 63);
	assert(i == 63);
}

void t_rmcp_session_get_confidentiality_payload_reserved_23()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.confidentiality_payload = 0;

	rmcp_session_set_confidentiality_payload_reserved_23(&r, 63);
	i = rmcp_session_get_confidentiality_payload_reserved_23(&r);
	// should always set zero
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_get_confidentiality_payload_length()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.confidentiality_payload = 0;

	rmcp_session_set_confidentiality_payload_length(&r, 63);
	i = rmcp_session_get_confidentiality_payload_length(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 63);
	assert(i == 63);
}

void t_rmcp_session_get_confidentiality_payload_algorithm()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.confidentiality_payload = 0;

	rmcp_session_set_confidentiality_payload_algorithm(&r, 12);
	i = rmcp_session_get_confidentiality_payload_algorithm(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 12);
	assert(i == 12);
}

void t_rmcp_session_get_confidentiality_payload_reserved_678()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t i;
	r.confidentiality_payload = 0;

	rmcp_session_set_confidentiality_payload_reserved_678(&r, 63);
	i = rmcp_session_get_confidentiality_payload_reserved_678(&r);
	// should always set zero
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", i, 0);
	assert(i == 0);
}

void t_rmcp_session_set_message_tag()
{
	struct rmcp_session r;
	r.message_tag = 0;
	printu(LOG_DEBUG, __func__);

	rmcp_session_set_message_tag(&r, 255);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_tag, 255);
	assert(r.message_tag == 255);
}

void t_rmcp_session_set_privilege_level_reserved()
{
	struct rmcp_session r;
	r.max_privilege_level = 255;
	printu(LOG_DEBUG, __func__);

	rmcp_session_set_privilege_level_reserved(&r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.max_privilege_level, 15);
	assert(r.max_privilege_level == 15);
}

void t_rmcp_session_set_privilege_level_request()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	r.max_privilege_level = 16;

	rmcp_session_set_privilege_level_request(&r, 5);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.max_privilege_level & 15, 5);
	assert((r.max_privilege_level & 15) == 5);
}

void t_rmcp_session_set_reserved()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	r.reserved = 1;
	rmcp_session_set_reserved(&r, 0);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.reserved, 0);
	assert(r.reserved == 0);
}

void t_rmcp_session_set_session_id()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	r.session_id = 1;
	rmcp_session_set_session_id(&r, 0);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.session_id, 0);
	assert(r.session_id == 0);
}

void t_rmcp_session_set_authentication_payload_type()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.authentication_payload = 18446744073709551615LU;
	rmcp_session_set_authentication_payload_type(&r, 8);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.authentication_payload, 648518346341351423);
	assert(r.authentication_payload == 648518346341351423);
}

void t_rmcp_session_set_authentication_payload_reserved_23()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.authentication_payload = 18446744073709551615LU;
	// always sets to 0
	rmcp_session_set_authentication_payload_reserved_23(&r, 256);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.authentication_payload, 18374687579183251455LU);
	assert(r.authentication_payload == 18374687579183251455LU);
}

void t_rmcp_session_set_authentication_payload_length()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.authentication_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_authentication_payload_length(&r, 8);
	// (2^64-1)-(2^40-1)+(2^35)+(2^32-1)
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.authentication_payload, 18446743012852629503LU);
	assert(r.authentication_payload == 18446743012852629503LU);
}

void t_rmcp_session_set_authentication_payload_algorithm()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.authentication_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_authentication_payload_algorithm(&r, 8);

	// (2^64-1)-(2^32-1)+(2^27)+(2^24-1)
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.authentication_payload, 18446744069565579263LU);
	assert(r.authentication_payload == 18446744069565579263LU);
}
void t_rmcp_session_set_authentication_payload_reserved_678()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.authentication_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_authentication_payload_reserved_678(&r, 8);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.authentication_payload, 18446744073692774400LU);
	assert(r.authentication_payload == 18446744073692774400LU);
}

void t_rmcp_session_set_integrity_payload_type()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.integrity_payload = 18446744073709551615LU;
	rmcp_session_set_integrity_payload_type(&r, 8);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.integrity_payload, 648518346341351423);
	assert(r.integrity_payload == 648518346341351423);
}

void t_rmcp_session_set_integrity_payload_reserved_23()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.integrity_payload = 18446744073709551615LU;
	// always sets to 0
	rmcp_session_set_integrity_payload_reserved_23(&r, 256);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.integrity_payload, 18374687579183251455LU);
	assert(r.integrity_payload == 18374687579183251455LU);
}

void t_rmcp_session_set_integrity_payload_length()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.integrity_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_integrity_payload_length(&r, 8);
	// (2^64-1)-(2^40-1)+(2^35)+(2^32-1)
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.integrity_payload, 18446743012852629503LU);
	assert(r.integrity_payload == 18446743012852629503LU);
}

void t_rmcp_session_set_integrity_payload_algorithm()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.integrity_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_integrity_payload_algorithm(&r, 8);

	// (2^64-1)-(2^32-1)+(2^27)+(2^24-1)
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.integrity_payload, 18446744069565579263LU);
	assert(r.integrity_payload == 18446744069565579263LU);
}
void t_rmcp_session_set_integrity_payload_reserved_678()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.integrity_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_integrity_payload_reserved_678(&r, 8);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.integrity_payload, 18446744073692774400LU);
	assert(r.integrity_payload == 18446744073692774400LU);
}

void t_rmcp_session_set_confidentiality_payload_type()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.confidentiality_payload = 18446744073709551615LU;
	rmcp_session_set_confidentiality_payload_type(&r, 8);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.confidentiality_payload, 648518346341351423);
	assert(r.confidentiality_payload == 648518346341351423);
}

void t_rmcp_session_set_confidentiality_payload_reserved_23()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.confidentiality_payload = 18446744073709551615LU;
	// always sets to 0
	rmcp_session_set_confidentiality_payload_reserved_23(&r, 256);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.confidentiality_payload, 18374687579183251455LU);
	assert(r.confidentiality_payload == 18374687579183251455LU);
}

void t_rmcp_session_set_confidentiality_payload_length()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.confidentiality_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_confidentiality_payload_length(&r, 8);
	// (2^64-1)-(2^40-1)+(2^35)+(2^32-1)
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.confidentiality_payload, 18446743012852629503LU);
	assert(r.confidentiality_payload == 18446743012852629503LU);
}

void t_rmcp_session_set_confidentiality_payload_algorithm()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.confidentiality_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_confidentiality_payload_algorithm(&r, 8);

	// (2^64-1)-(2^32-1)+(2^27)+(2^24-1)
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.confidentiality_payload, 18446744069565579263LU);
	assert(r.confidentiality_payload == 18446744069565579263LU);
}
void t_rmcp_session_set_confidentiality_payload_reserved_678()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	//2^64-1
	r.confidentiality_payload = 18446744073709551615LU;
	// does nothing
	rmcp_session_set_confidentiality_payload_reserved_678(&r, 8);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", r.confidentiality_payload, 18446744073692774400LU);
	assert(r.confidentiality_payload == 18446744073692774400LU);
}

void t_rmcp_session_pack_message_tag()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];
	uint8_t i;

	r.message_tag = 64;
	rmcp_session_header_pack_message_tag(d, &r);
	r.message_tag = 0;
	rmcp_session_header_unpack_message_tag(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_tag, 64);
	assert(r.message_tag == 64);
}

void t_rmcp_session_pack_privilege_level()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];

	r.max_privilege_level = 64;
	rmcp_session_header_pack_privilege_level(d, &r);
	r.max_privilege_level = 0;
	rmcp_session_header_unpack_privilege_level(d, &r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.max_privilege_level, 64);
	assert(r.max_privilege_level == 64);
}
void t_rmcp_session_pack_reserved()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];

	r.reserved = 65535;
	rmcp_session_header_pack_reserved(d, &r);
	r.reserved = 0;
	rmcp_session_header_unpack_reserved(d, &r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.reserved, 65535);
	assert(r.reserved == 65535);
}
void t_rmcp_session_pack_session_id()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];

	r.session_id = 4294967295;
	rmcp_session_header_pack_session_id(d, &r);
	r.session_id = 0;
	rmcp_session_header_unpack_session_id(d, &r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.session_id, 4294967295);
	assert(r.session_id == 4294967295);
}

void t_rmcp_session_unpack_message_tag()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];
	uint8_t i;

	r.message_tag = 64;
	rmcp_session_header_pack_message_tag(d, &r);
	r.message_tag = 0;
	rmcp_session_header_unpack_message_tag(d, &r);

	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.message_tag, 64);
	assert(r.message_tag == 64);
}

void t_rmcp_session_unpack_privilege_level()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];

	r.max_privilege_level = 64;
	rmcp_session_header_pack_privilege_level(d, &r);
	r.max_privilege_level = 0;
	rmcp_session_header_unpack_privilege_level(d, &r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.max_privilege_level, 64);
	assert(r.max_privilege_level == 64);
}
void t_rmcp_session_unpack_reserved()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];

	r.reserved = 65535;
	rmcp_session_header_pack_reserved(d, &r);
	r.reserved = 0;
	rmcp_session_header_unpack_reserved(d, &r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.reserved, 65535);
	assert(r.reserved == 65535);
}
void t_rmcp_session_unpack_session_id()
{
	printu(LOG_DEBUG, __func__);
	struct rmcp_session r;
	uint8_t d[32 * 8];

	r.session_id = 4294967295;
	rmcp_session_header_pack_session_id(d, &r);
	r.session_id = 0;
	rmcp_session_header_unpack_session_id(d, &r);
	printu(LOG_DEBUG, "\t\tassert(%u == %u)", r.session_id, 4294967295);
	assert(r.session_id == 4294967295);
}

void t_unpackl()
{
	/*
	* (2^0)+(2^9)+(2^16+2^17)+(2^26) = 67305985
	*/
	uint8_t d[] = { 1, 2, 3, 4 };
	uint64_t i;
	printu(LOG_DEBUG, __func__);

	i = unpackl(d, 4);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", i, 67305985);
	assert(i == 67305985);
}
void t_unpackr()
{
	/*
	* (2^2)+(2^8)+(2^9)+(2^17)+(2^24) = 16909060
	*/
	uint8_t d[] = { 1, 2, 3, 4 };
	uint64_t i;
	printu(LOG_DEBUG, __func__);

	i = unpackr(d, 4);
	printu(LOG_DEBUG, "\t\tassert(%lu == %lu)", i, 616909060);
	assert(i == 16909060);
}

void test_unpack_functions()
{
	/*
	* the unpack portion of the exam, assert that we can take arbitrary data from
	* a location and shove it in the proper unsigned integer sizes
	*/
	printf("\n");
	printu(LOG_INFO, __func__);
	t_asf_msg_data_unpack_iana();
	t_asf_msg_data_unpack_oem();
	t_asf_msg_data_unpack_supported_entities();

	t_asf_msg_header_unpack_iana();
	t_asf_msg_header_unpack_type();
	t_asf_msg_header_unpack_tag();
	t_asf_msg_header_unpack_reserved();
	t_asf_msg_header_unpack_data_length();

	t_rmcp_msg_header_unpack_version();
	t_rmcp_msg_header_unpack_reserved();
	t_rmcp_msg_header_unpack_sequence_number();
	t_rmcp_msg_header_unpack_message_class();

	t_rmcp_session_unpack_message_tag();
	t_rmcp_session_unpack_privilege_level();
	t_rmcp_session_unpack_reserved();
	t_rmcp_session_unpack_session_id();
	t_unpackl();
	t_unpackr();
}

void test_set_functions()
{
	/*
	* the bit-twiddling set tests
	*/
	printu(LOG_INFO, __func__);

	t_asf_msg_data_set_iana();
	t_asf_msg_data_set_oem();
	t_asf_msg_data_set_supported_entities_ipmi();
	t_asf_msg_data_set_supported_entities_version();
	t_asf_msg_data_set_supported_interactions_security();
	t_asf_msg_data_set_supported_interactions_dash();
	t_asf_msg_data_set_supported_interactions_reserved();

	t_asf_msg_header_set_iana();
	t_asf_msg_header_set_reserved();
	t_asf_msg_header_set_type();
	t_asf_msg_header_set_tag();
	t_asf_msg_header_set_length();

	t_rmcp_msg_header_set_version();
	t_rmcp_msg_header_set_reserved();
	t_rmcp_msg_header_set_sequence();
	t_rmcp_msg_header_set_class_type();
	t_rmcp_msg_header_set_class_tag();

	t_rmcp_session_set_message_tag();
	t_rmcp_session_set_privilege_level_reserved();
	t_rmcp_session_set_privilege_level_request();
	t_rmcp_session_set_reserved();
	t_rmcp_session_set_session_id();
	t_rmcp_session_set_authentication_payload_type();
	t_rmcp_session_set_authentication_payload_reserved_23();
	t_rmcp_session_set_authentication_payload_length();
	t_rmcp_session_set_authentication_payload_algorithm();
	t_rmcp_session_set_authentication_payload_reserved_678();
	t_rmcp_session_set_authentication_payload_type();
	t_rmcp_session_set_authentication_payload_reserved_23();
	t_rmcp_session_set_authentication_payload_length();
	t_rmcp_session_set_authentication_payload_algorithm();
	t_rmcp_session_set_authentication_payload_reserved_678();
	t_rmcp_session_set_integrity_payload_type();
	t_rmcp_session_set_integrity_payload_reserved_23();
	t_rmcp_session_set_integrity_payload_length();
	t_rmcp_session_set_integrity_payload_algorithm();
	t_rmcp_session_set_integrity_payload_reserved_678();
	t_rmcp_session_set_confidentiality_payload_type();
	t_rmcp_session_set_confidentiality_payload_reserved_23();
	t_rmcp_session_set_confidentiality_payload_length();
	t_rmcp_session_set_confidentiality_payload_algorithm();
	t_rmcp_session_set_confidentiality_payload_reserved_678();
}

void test_get_functions()
{
	printf("\n");
	printu(LOG_INFO, __func__);
	t_rmcp_msg_header_get_class_tag();
	t_rmcp_msg_header_get_class_ack();
	t_rmcp_msg_header_get_version();
	t_rmcp_msg_header_get_reserved();
	t_rmcp_msg_header_get_sequence();

	t_asf_msg_data_get_iana();
	t_asf_msg_data_get_oem();
	t_asf_msg_data_get_supported_entities_ipmi();
	t_asf_msg_data_get_supported_entities_version();
	t_asf_msg_data_get_supported_interactions_security();
	t_asf_msg_data_get_supported_interactions_dash();

	t_asf_msg_header_get_iana();
	t_asf_msg_header_get_length();
	t_asf_msg_header_get_reserved();
	t_asf_msg_header_get_tag();

	t_rmcp_session_get_message_tag();
	t_rmcp_session_get_privilege_level_reserved();
	t_rmcp_session_get_privilege_level_request();
	t_rmcp_session_get_session_id();

	t_rmcp_session_get_authentication_payload_type();
	t_rmcp_session_get_authentication_payload_reserved_23();
	t_rmcp_session_get_authentication_payload_length();
	t_rmcp_session_get_authentication_payload_algorithm();
	t_rmcp_session_get_authentication_payload_reserved_678();

	t_rmcp_session_get_integrity_payload_type();
	t_rmcp_session_get_integrity_payload_reserved_23();
	t_rmcp_session_get_integrity_payload_length();
	t_rmcp_session_get_integrity_payload_algorithm();
	t_rmcp_session_get_integrity_payload_reserved_678();

	t_rmcp_session_get_confidentiality_payload_type();
	t_rmcp_session_get_confidentiality_payload_reserved_23();
	t_rmcp_session_get_confidentiality_payload_length();
	t_rmcp_session_get_confidentiality_payload_algorithm();
	t_rmcp_session_get_confidentiality_payload_reserved_678();
}

void test_pack_functions()
{
	printf("\n");
	printu(LOG_INFO, __func__);
	t_asf_msg_data_pack_iana();
	t_asf_msg_data_pack_oem();
	t_asf_msg_data_pack_supported_entities();
	t_asf_msg_data_pack_supported_interactions();

	t_asf_msg_header_pack_iana();
	t_asf_msg_header_pack_type();
	t_asf_msg_header_pack_tag();
	t_asf_msg_header_pack_reserved();

	t_rmcp_msg_header_pack_version();
	t_rmcp_msg_header_pack_reserved();
	t_rmcp_msg_header_pack_sequence_number();
	t_rmcp_msg_header_pack_message_class();

	t_rmcp_session_pack_message_tag();
	t_rmcp_session_pack_privilege_level();
	t_rmcp_session_pack_reserved();
	t_rmcp_session_pack_session_id();
}
int main(void)
{
	setprintmask(LOG_DEBUG);
	test_unpack_functions();
	test_pack_functions();
	test_set_functions();
	test_get_functions();
	return 0;
}
