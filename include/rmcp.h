#ifndef RMCP
#define RMCP
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
#include <stdlib.h>
enum {
	/*
	*  network and session stuff
	*/
	RMCP_PORT_SECURE = 664,
	RMCP_PORT_CLEAR = 623,
	ASF_SESSION_PING = 80,
};
enum {
	/*
	*  rmcp header
	*/
	RMCP_MSG_HEADER_CLASS_ASF = 6,
	RMCP_MSG_HEADER_CLASS_IPMI = 7,
	RMCP_MSG_HEADER_CLASS_OEM = 8,
	RMCP_MSG_HEADER_VERSION_OFFSET = 0,
	RMCP_MSG_HEADER_VERSION_SIZE = sizeof(uint8_t),
	RMCP_MSG_HEADER_RESERVED_OFFSET = RMCP_MSG_HEADER_VERSION_OFFSET + RMCP_MSG_HEADER_VERSION_SIZE,
	RMCP_MSG_HEADER_RESERVED_SIZE = sizeof(uint8_t),
	RMCP_MSG_HEADER_SEQUENCE_OFFSET = RMCP_MSG_HEADER_RESERVED_OFFSET + RMCP_MSG_HEADER_RESERVED_SIZE,
	RMCP_MSG_HEADER_SEQUENCE_SIZE = sizeof(uint8_t),
	RMCP_MSG_HEADER_CLASS_OFFSET = RMCP_MSG_HEADER_SEQUENCE_OFFSET + RMCP_MSG_HEADER_SEQUENCE_SIZE,
	RMCP_MSG_HEADER_CLASS_SIZE = sizeof(uint8_t),
};
enum {
	/*
	* asf header
	* there isn't an asf header defined in the spec. we've just separated
	* the data from the rest of the message.
	*/
	ASF_MSG_HEADER_IANA_OFFSET = RMCP_MSG_HEADER_CLASS_OFFSET + RMCP_MSG_HEADER_CLASS_SIZE,
	ASF_MSG_HEADER_IANA_SIZE = sizeof(uint32_t),
	ASF_MSG_HEADER_TYPE_OFFSET = ASF_MSG_HEADER_IANA_OFFSET + ASF_MSG_HEADER_IANA_SIZE,
	ASF_MSG_HEADER_TYPE_SIZE = sizeof(uint8_t),
	ASF_MSG_HEADER_TAG_OFFSET = ASF_MSG_HEADER_TYPE_OFFSET + ASF_MSG_HEADER_TYPE_SIZE,
	ASF_MSG_HEADER_TAG_SIZE = sizeof(uint8_t),
	ASF_MSG_HEADER_RESERVED_OFFSET = ASF_MSG_HEADER_TAG_OFFSET + ASF_MSG_HEADER_TAG_SIZE,
	ASF_MSG_HEADER_RESERVED_SIZE = sizeof(uint8_t),
	ASF_MSG_HEADER_DATA_LEN_OFFSET = ASF_MSG_HEADER_RESERVED_OFFSET + ASF_MSG_HEADER_RESERVED_SIZE,
	ASF_MSG_HEADER_DATA_LEN_SIZE = sizeof(uint8_t),
	ASF_MSG_PING_LEN = ASF_MSG_HEADER_DATA_LEN_OFFSET + ASF_MSG_HEADER_DATA_LEN_SIZE,
};
enum {
	/*
	* asf data
	* as stated above, there isn't an asf data defined in the spec.  We just use
	* this for the payload.
	*/
	ASF_MSG_DATA_IANA_OFFSET = ASF_MSG_HEADER_DATA_LEN_OFFSET + ASF_MSG_HEADER_DATA_LEN_SIZE,
	ASF_MSG_DATA_IANA_SIZE = sizeof(uint32_t),
	ASF_MSG_DATA_OEM_OFFSET = ASF_MSG_DATA_IANA_OFFSET + ASF_MSG_DATA_IANA_SIZE,
	ASF_MSG_DATA_OEM_SIZE = sizeof(uint32_t),
	ASF_MSG_DATA_SUP_ENT_OFFSET = ASF_MSG_DATA_OEM_OFFSET + ASF_MSG_DATA_OEM_SIZE,
	ASF_MSG_DATA_SUP_ENT_SIZE = sizeof(uint8_t),
	ASF_MSG_DATA_SUP_INT_OFFSET = ASF_MSG_DATA_SUP_ENT_OFFSET + ASF_MSG_DATA_SUP_ENT_SIZE,
	ASF_MSG_DATA_SUP_INT_SIZE = sizeof(uint8_t),
	ASF_MSG_DATA_RESERVED_DATA_OFFSET = ASF_MSG_DATA_SUP_INT_OFFSET + ASF_MSG_DATA_SUP_INT_SIZE,
	ASF_MSG_DATA_RESERVED_DATA_SIZE = sizeof(uint8_t) * 6,
	LONGEST = ASF_MSG_DATA_RESERVED_DATA_OFFSET + ASF_MSG_DATA_RESERVED_DATA_SIZE,
};
enum {
	/*
	* rcmp open session request data
	*/
	RMCP_SESSION_MESSAGE_TAG_OFFSET = 0,
	RMCP_SESSION_MESSAGE_TAG_SIZE = sizeof(uint8_t),
	RMCP_SESSION_MAX_PRIV_LEVEL_OFFSET = RMCP_SESSION_MESSAGE_TAG_OFFSET + RMCP_SESSION_MESSAGE_TAG_SIZE,
	RMCP_SESSION_MAX_PRIV_LEVEL_SIZE = sizeof(uint8_t),
	RMCP_SESSION_RESERVED_OFFSET = RMCP_SESSION_MAX_PRIV_LEVEL_OFFSET + RMCP_SESSION_MAX_PRIV_LEVEL_SIZE,
	RMCP_SESSION_RESERVED_SIZE = sizeof(uint16_t),
	RMCP_SESSION_SESSION_ID_OFFSET = RMCP_SESSION_RESERVED_OFFSET + RMCP_SESSION_RESERVED_SIZE,
	RMCP_SESSION_SESSION_ID_SIZE = sizeof(uint32_t),
	RMCP_SESSION_AUTHENTICATION_PAYLOAD_OFFSET = RMCP_SESSION_RESERVED_SIZE + RMCP_SESSION_SESSION_ID_OFFSET,
	RMCP_SESSION_AUTHENTICATION_PAYLOAD_SIZE = sizeof(uint64_t),
	RMCP_SESSION_INTEGRITY_PAYLOAD_OFFSET = RMCP_SESSION_AUTHENTICATION_PAYLOAD_OFFSET + RMCP_SESSION_AUTHENTICATION_PAYLOAD_SIZE,
	RMCP_SESSION_INTEGRITY_PAYLOAD_SIZE = sizeof(uint64_t),
	RMCP_SESSION_CONFIDENTIALITY_PAYLOAD = RMCP_SESSION_INTEGRITY_PAYLOAD_OFFSET + RMCP_SESSION_INTEGRITY_PAYLOAD_SIZE,
};

enum {
	RMCP_SESSION_PRIVILEGE_UNDEFINED = 0,
	RMCP_SESSION_PRIVILEGE_CALLBACK = 1,
	RMCP_SESSION_PRIVILEGE_USER = 2,
	RMCP_SESSION_PRIVILEGE_OPERATOR = 3,
	RMCP_SESSION_PRIVILEGE_ADMINISTRATOR = 4,
	RMCP_SESSION_PRIVILEGE_OEM = 5,
};

struct rmcp_header {
	uint8_t version;
	uint8_t reserved;
	uint8_t sequence_number;
	uint8_t message_class;
};
struct rmcp_session {
	uint8_t message_tag;
	uint8_t max_privilege_level;
	uint16_t reserved;
	uint32_t session_id;
	uint64_t authentication_payload;
	uint64_t integrity_payload;
	uint64_t confidentiality_payload;
};
struct asf_header {
	uint32_t iana_number;
	uint8_t type;
	uint8_t tag;
	uint8_t reserved;
	uint8_t data_length;
};
struct asf_data {
	uint32_t iana_number;
	uint32_t oem_defined;
	uint8_t supported_entities;
	uint8_t supported_interactions;
	uint8_t reserved;
};
uint64_t unpackl(uint8_t *d, size_t l);
uint64_t unpackr(uint8_t *d, size_t l);
void packl(uint8_t *d, uint64_t s, size_t l);
void packr(uint8_t *d, uint64_t s, size_t l);
void asf_msg_data_pack_iana(uint8_t *d, struct asf_data *a);
void asf_msg_data_pack_oem(uint8_t *d, struct asf_data *a);
void asf_msg_data_pack_supported_entities(uint8_t *d, struct asf_data *);
void asf_msg_data_pack_supported_interactions(uint8_t *d, struct asf_data *);
uint32_t asf_msg_data_get_iana(struct asf_data *a);
uint32_t asf_msg_data_get_oem(struct asf_data *a);
uint8_t asf_msg_data_get_supported_entities_ipmi(struct asf_data *a);
uint8_t asf_msg_data_get_supported_entities_version(struct asf_data *a);
uint8_t asf_msg_data_get_supported_interactions_security(struct asf_data *a);
uint8_t asf_msg_data_get_supported_interactions_dash(struct asf_data *a);
void asf_msg_data_set_iana(struct asf_data *a, uint32_t i);
void asf_msg_data_set_oem(struct asf_data *a, uint32_t i);
void asf_msg_data_set_supported_entities_ipmi(struct asf_data *a, uint32_t i);
void asf_msg_data_set_supported_entities_version(struct asf_data *a);
void asf_msg_data_set_supported_interactions_security(struct asf_data *a, uint8_t i);
void asf_msg_data_set_supported_interactions_dash(struct asf_data *a, uint8_t i);
void asf_msg_data_set_supported_interactions_reserved(struct asf_data *a);
void asf_msg_data_unpack_iana(uint8_t *d, struct asf_data *a);
void asf_msg_data_unpack_oem(uint8_t *d, struct asf_data *a);
void asf_msg_data_unpack_supported_entities(uint8_t *d, struct asf_data *a);
void asf_msg_data_unpack_supported_interactions(uint8_t *d, struct asf_data *a);
uint32_t asf_msg_header_get_iana(struct asf_header *a);
uint8_t asf_msg_header_get_length(struct asf_header *a);
uint8_t asf_msg_header_get_reserved(struct asf_header *a);
uint8_t asf_msg_header_get_tag(struct asf_header *a);
uint8_t asf_msg_header_get_type(struct asf_header *a);
void asf_msg_header_pack_iana(uint8_t *d, struct asf_header *a);
void asf_msg_header_pack_type(uint8_t *d, struct asf_header *a);
void asf_msg_header_pack_tag(uint8_t *d, struct asf_header *a);
void asf_msg_header_pack_reserved(uint8_t *d, struct asf_header *a);
void asf_msg_header_pack_data_length(uint8_t *d, struct asf_header *a);
void asf_msg_header_unpack_iana(uint8_t *d, struct asf_header *a);
void asf_msg_header_unpack_type(uint8_t *d, struct asf_header *a);
void asf_msg_header_unpack_tag(uint8_t *d, struct asf_header *a);
void asf_msg_header_unpack_reserved(uint8_t *d, struct asf_header *a);
void asf_msg_header_unpack_data_length(uint8_t *d, struct asf_header *a);
void asf_msg_header_set_iana(struct asf_header *a);
void asf_msg_header_set_length(struct asf_header *a, uint8_t i);
void asf_msg_header_set_reserved(struct asf_header *a);
void asf_msg_header_set_tag(struct asf_header *a, uint8_t i);
void asf_msg_header_set_type(struct asf_header *a, uint8_t i);
uint8_t rmcp_msg_header_get_class_tag(struct rmcp_header *r);
uint8_t rmcp_msg_header_get_class_ack(struct rmcp_header *r);
uint8_t rmcp_msg_header_get_reserved(struct rmcp_header *r);
uint8_t rmcp_msg_header_get_sequence(struct rmcp_header *r);
uint8_t rmcp_msg_header_get_version(struct rmcp_header *r);
void rmcp_msg_header_pack_version(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_pack_reserved(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_pack_sequence_number(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_pack_message_class(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_set_class_tag(struct rmcp_header *r, uint8_t i);
void rmcp_msg_header_set_class_type(struct rmcp_header *r, uint8_t ack);
void rmcp_msg_header_set_reserved(struct rmcp_header *r);
void rmcp_msg_header_set_sequence(struct rmcp_header *r, uint8_t i);
void rmcp_msg_header_set_version(struct rmcp_header *r);
void rmcp_msg_header_unpack_version(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_unpack_reserved(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_unpack_sequence_number(uint8_t *d, struct rmcp_header *r);
void rmcp_msg_header_unpack_message_class(uint8_t *d, struct rmcp_header *r);
uint8_t rmcp_session_get_message_tag(struct rmcp_session *r);
uint8_t rmcp_session_get_privilege_level_reserved(struct rmcp_session *r);
uint8_t rmcp_session_get_privilege_level_request(struct rmcp_session *r);
uint32_t rmcp_session_get_session_id(struct rmcp_session *r);
uint8_t rmcp_session_get_authentication_payload_type(struct rmcp_session *r);
uint16_t rmcp_session_get_authentication_payload_reserved_23(struct rmcp_session *r);
uint8_t rmcp_session_get_authentication_payload_length(struct rmcp_session *r);
uint8_t rmcp_session_get_authentication_payload_algorithm(struct rmcp_session *r);
uint32_t rmcp_session_get_authentication_payload_reserved_678(struct rmcp_session *r);
uint8_t rmcp_session_get_integrity_payload_type(struct rmcp_session *r);
uint16_t rmcp_session_get_integrity_payload_reserved_23(struct rmcp_session *r);
uint8_t rmcp_session_get_integrity_payload_length(struct rmcp_session *r);
uint8_t rmcp_session_get_integrity_payload_algorithm(struct rmcp_session *r);
uint32_t rmcp_session_get_integrity_payload_reserved_678(struct rmcp_session *r);
uint8_t rmcp_session_get_confidentiality_payload_type(struct rmcp_session *r);
uint16_t rmcp_session_get_confidentiality_payload_reserved_23(struct rmcp_session *r);
uint8_t rmcp_session_get_confidentiality_payload_length(struct rmcp_session *r);
uint8_t rmcp_session_get_confidentiality_payload_algorithm(struct rmcp_session *r);
uint32_t rmcp_session_get_confidentiality_payload_reserved_678(struct rmcp_session *r);
void rmcp_session_set_message_tag(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_privilege_level_reserved(struct rmcp_session *r);
void rmcp_session_set_privilege_level_request(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_reserved(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_session_id(struct rmcp_session *r, uint32_t i);
void rmcp_session_set_authentication_payload_type(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_authentication_payload_reserved_23(struct rmcp_session *r, uint16_t i);
void rmcp_session_set_authentication_payload_length(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_authentication_payload_algorithm(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_authentication_payload_reserved_678(struct rmcp_session *r, uint32_t i);
void rmcp_session_set_integrity_payload_type(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_integrity_payload_reserved_23(struct rmcp_session *r, uint16_t i);
void rmcp_session_set_integrity_payload_length(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_integrity_payload_algorithm(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_integrity_payload_reserved_678(struct rmcp_session *r, uint32_t i);
void rmcp_session_set_confidentiality_payload_type(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_confidentiality_payload_reserved_23(struct rmcp_session *r, uint16_t i);
void rmcp_session_set_confidentiality_payload_length(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_confidentiality_payload_algorithm(struct rmcp_session *r, uint8_t i);
void rmcp_session_set_confidentiality_payload_reserved_678(struct rmcp_session *r, uint32_t i);
void rmcp_session_header_pack_message_tag(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_pack_privilege_level(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_pack_reserved(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_pack_session_id(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_pack_authentication_payload(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_pack_integrity_payload(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_pack_confidentiality_payload(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_message_tag(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_privilege_level(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_reserved(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_session_id(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_authentication_payload(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_integrity_payload(uint8_t *d, struct rmcp_session *r);
void rmcp_session_header_unpack_confidentiality_payload(uint8_t *d, struct rmcp_session *r);

#endif
