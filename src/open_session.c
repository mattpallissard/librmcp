#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <rmcp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void rmcp_header_print(struct rmcp_header *r)
{
	printf("rmcp version:                      %u\n", rmcp_msg_header_get_version(r));
	printf("rmcp sequence:                     %u\n", rmcp_msg_header_get_sequence(r));
	printf("rmcp reserved:                     %u\n", rmcp_msg_header_get_reserved(r));
	printf("rmcp class ack                     %u\n", rmcp_msg_header_get_class_ack(r));
	printf("rmcp class tag:                    %u\n\n", rmcp_msg_header_get_class_tag(r));
}

void rmcp_header_set(struct rmcp_header *r)
{
	rmcp_msg_header_set_version(r);
	rmcp_msg_header_set_sequence(r, 0);
	rmcp_msg_header_set_class_tag(r, RMCP_MSG_HEADER_CLASS_IPMI);
	rmcp_msg_header_set_reserved(r);
	rmcp_msg_header_set_class_type(r, 0);
}

void rmcp_header_pack(uint8_t *d, struct rmcp_header *r)
{
	rmcp_msg_header_pack_version(d, r);
	rmcp_msg_header_pack_reserved(d, r);
	rmcp_msg_header_pack_sequence_number(d, r);
	rmcp_msg_header_pack_message_class(d, r);
}

void rmcp_header_unpack(uint8_t *d, struct rmcp_header *r)
{
	rmcp_msg_header_unpack_version(d, r);
	rmcp_msg_header_unpack_reserved(d, r);
	rmcp_msg_header_unpack_sequence_number(d, r);
	rmcp_msg_header_unpack_message_class(d, r);
}

void rmcp_session_unpack(uint8_t *d, struct rmcp_session *r)
{
	rmcp_session_header_unpack_message_tag(d, r);
	rmcp_session_header_unpack_privilege_level(d, r);
	rmcp_session_header_unpack_reserved(d, r);
	rmcp_session_header_unpack_session_id(d, r);
	rmcp_session_header_unpack_authentication_payload(d, r);
	rmcp_session_header_unpack_integrity_payload(d, r);
	rmcp_session_header_unpack_confidentiality_payload(d, r);
}

void rmcp_session_print(struct rmcp_session *r)
{
	printf("message tag:                       %u\n", rmcp_session_get_message_tag(r));
	printf("level requested:                   %u\n", rmcp_session_get_privilege_level_request(r));
	printf("session id:                        %u\n\n", rmcp_session_get_session_id(r));
	printf("reserved:                          %u\n", rmcp_session_get_reserved(r));

	printf("authentication payload type:       %u\n", rmcp_session_get_authentication_payload_type(r));
	printf("authentication reserved 23:        %u\n", rmcp_session_get_authentication_payload_reserved_23(r));
	printf("authentication payload length:     %u\n", rmcp_session_get_authentication_payload_length(r));
	printf("authentication payoad algorithm:   %u\n", rmcp_session_get_authentication_payload_algorithm(r));
	printf("authentication reserved 678:       %u\n\n", rmcp_session_get_authentication_payload_reserved_678(r));

	printf("integrity payload type:            %u\n", rmcp_session_get_integrity_payload_type(r));
	printf("integrity reserved 23:             %u\n", rmcp_session_get_integrity_payload_reserved_23(r));
	printf("integrity payload length:          %u\n", rmcp_session_get_integrity_payload_length(r));
	printf("integrity payload algorithm:       %u\n", rmcp_session_get_integrity_payload_algorithm(r));
	printf("integrity reserved 678             %u\n\n", rmcp_session_get_integrity_payload_reserved_678(r));

	printf("confidentiality payload type:      %u\n", rmcp_session_get_confidentiality_payload_type(r));
	printf("confidentiality reserved 23:       %u\n", rmcp_session_get_confidentiality_payload_reserved_23(r));
	printf("confidentiality payload length:    %u\n", rmcp_session_get_confidentiality_payload_length(r));
	printf("confidentiality payload algorithm: %u\n", rmcp_session_get_confidentiality_payload_algorithm(r));
	printf("confidentiality reserved 678       %u\n\n", rmcp_session_get_confidentiality_payload_reserved_678(r));
}

void rmcp_session_set(struct rmcp_session *r)
{
	rmcp_session_set_message_tag(r, 0);
	rmcp_session_set_privilege_level_reserved(r);
	rmcp_session_set_privilege_level_request(r, RMCP_SESSION_PRIVILEGE_UNDEFINED);
	rmcp_session_set_reserved(r, 0);
	rmcp_session_set_session_id(r, 0);

	rmcp_session_set_authentication_payload_type(r, 0);
	rmcp_session_set_authentication_payload_reserved_23(r, 0);
	rmcp_session_set_authentication_payload_length(r, 8);
	rmcp_session_set_authentication_payload_algorithm(r, RMCP_AUTHENTICATION_ALGORITHM_NONE);
	rmcp_session_set_authentication_payload_reserved_678(r, 0);

	rmcp_session_set_integrity_payload_type(r, 0);
	rmcp_session_set_integrity_payload_reserved_23(r, 0);
	rmcp_session_set_integrity_payload_length(r, 8);
	rmcp_session_set_integrity_payload_algorithm(r, RMCP_INTEGRITY_ALGORITHM_NONE);
	rmcp_session_set_integrity_payload_reserved_678(r, 0);

	rmcp_session_set_confidentiality_payload_type(r, 0);
	rmcp_session_set_confidentiality_payload_reserved_23(r, 0);
	rmcp_session_set_confidentiality_payload_length(r, 8);
	rmcp_session_set_confidentiality_payload_algorithm(r, RMCP_CONFIDENTIALITY_ALGORITHM_NONE);
	rmcp_session_set_confidentiality_payload_reserved_678(r, 0);
}

void rmcp_session_pack(uint8_t *d, struct rmcp_session *r)
{
	rmcp_session_header_pack_message_tag(d, r);
	rmcp_session_header_pack_privilege_level(d, r);
	rmcp_session_header_pack_reserved(d, r);
	rmcp_session_header_pack_session_id(d, r);
	rmcp_session_header_pack_authentication_payload(d, r);
	rmcp_session_header_pack_integrity_payload(d, r);
	rmcp_session_header_pack_confidentiality_payload(d, r);
}

void udp(uint8_t *d, uint8_t *r)
{
	int l, fd;
	struct sockaddr_in s;
	memset(&s, 0, sizeof(s));

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 || errno)
		goto out;

	s.sin_family = AF_INET;
	s.sin_port = htons(RMCP_PORT_CLEAR);
	s.sin_addr.s_addr = inet_addr("192.168.1.16");
	l = sizeof(s);

	if ((connect(fd, (struct sockaddr *)&s, l) < 0) || errno)
		goto out;

	if ((sendto(fd, d, RMCP_SESSION_LONGEST, 0, (struct sockaddr *)NULL, l) < 0) || errno)
		goto out;

	if ((recvfrom(fd, r, RMCP_SESSION_LONGEST, 0, (struct sockaddr *)NULL, NULL) < 0) || errno)
		goto out;

	return;

out:
	fprintf(stderr, "%s: (%d) %s\n", __func__, errno, strerror(errno));
	exit(1);
}

int main(void)
{
	struct rmcp_header rh;
	struct rmcp_session rs;

	uint8_t ds[RMCP_SESSION_LONGEST];
	uint8_t dr[RMCP_SESSION_LONGEST];
	memset(ds, '\0', RMCP_SESSION_LONGEST);
	memset(dr, '\0', RMCP_SESSION_LONGEST);

	rmcp_header_set(&rh);
	rmcp_header_print(&rh);

	rmcp_session_set(&rs);
	rmcp_session_print(&rs);
	printf("\n\n");

	rmcp_header_pack(ds, &rh);
	rmcp_session_pack(ds, &rs);

	udp(ds, dr);

	memset(&rh, '\0', sizeof(rh));
	memset(&rs, '\0', sizeof(rs));

	rmcp_header_unpack(dr, &rh);
	rmcp_session_unpack(dr, &rs);

	rmcp_session_set(&rs);
	rmcp_session_print(&rs);
}
