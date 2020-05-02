#include <stdint.h>
enum {
	// ipmi auth types
	IPMI_AUTH_NONE = 0,
	IPMI_AUTH_MD2 = 1,
	IPMI_AUTH_MD5 = 2,
	IPMI_AUTH_RESERVED = 3,
	IPMI_AUTH_KEY = 4,
	IPMI_AUTH_OEM = 5,
	IPMI_AUTH_FORMAT = 6,
};

enum {
	// roles (privilege level)
	IPMI_ROLE_HIGHEST = 0,
	IPMI_ROLE_CALLBACK = 1,
	IPMI_ROLE_USER = 2,
	IPMI_ROLE_OPERATOR = 3,
	IPMI_ROLE_ADMINISTRATOR = 4,
	IPMI_ROLE_OEM = 5,
};

enum {
	// payload numbers
	IPMI_PAYLOAD_NUM_MESSAGE = 0,
	IPMI_PAYLOAD_NUM_SOL = 1,
	IPMI_PAYLOAD_NUM_OEM = 2,
	IPMI_PAYLOAD_NUM_RMCP_OPEN_REQ = 16,
	IPMI_PAYLOAD_NUM_RMCP_OPEN_RES = 17,
	IPMI_PAYLOAD_NUM_RAKP_1 = 18,
	IPMI_PAYLOAD_NUM_RAKP_2 = 19,
	IPMI_PAYLOAD_NUM_RAKP_3 = 20,
	IPMI_PAYLOAD_NUM_RAKP_4 = 21,
	// 20-> 27 OEM
};

enum {
	// algo numbers
	IPMI_ALGO_RAKP_NONE = 0,
	IPMI_ALGO_RAKP_HMAC_SHA1 = 1,
	IPMI_ALGO_RAKP_HMAC_MD5 = 2,
	IPMI_ALGO_RAKP_HMAC_SHA256 = 3,
	// 192 -> 255 =  OEM,  all other reserved
};

// p159
struct ipmi_session_header {
	uint8_t auth_type;
	uint8_t payload_type;
	uint32_t oem_iana;
	uint16_t oem_payload_id;
	uint32_t rmcp_session_id; // ipmi2.0/rmcp+
	uint32_t rmcp_session_sequence_number;
	uint32_t ipmi_session_id; // ipmi1.5
	uint8_t msg_auth_code_code[16];
	uint16_t payload_length;
};

struct ipmi_session_payload {
	uint8_t message_tag;
	uint8_t status_code; // not in request
	uint8_t role;
	uint16_t reserved;
	uint32_t remote_console_session_id;
	uint64_t authentication_payload;
	uint64_t integrity_payload;
	uint64_t confidentiality_payload;
};

struct ipmi_msg_payload {
	// Do I need this?
	uint8_t *confidentiality_header;
	uint8_t *payload_data;
	uint8_t *confidentiality_trailer;
};

struct ipmi_session_trailer {
	uint8_t *integrity_pad;
	uint8_t pad_length;
	uint8_t next_header;
	uint8_t *auth_code;
	uint8_t legacy_pad; //ipmi 1.5
};
