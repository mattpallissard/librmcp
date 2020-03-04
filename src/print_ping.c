/*
Copyright (c) 2010 matt pallissard

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

void rmcp_header_set(struct rmcp_header *r)
{
	rmcp_msg_header_set_version(r);
	rmcp_msg_header_set_sequence(r, 255);
	rmcp_msg_header_set_class_tag(r, 6);
	rmcp_msg_header_set_reserved(r);
	rmcp_msg_header_set_class_type(r, 0);
}

void asf_header_set(struct asf_header *a)
{
	asf_msg_header_set_iana(a);
	asf_msg_header_set_type(a, 0x80);
	asf_msg_header_set_tag(a, 1);
	asf_msg_header_set_reserved(a);
	asf_msg_header_set_length(a, 0);
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

void asf_header_pack(uint8_t *d, struct asf_header *a)
{
	asf_msg_header_pack_iana(d, a);
	asf_msg_header_pack_type(d, a);
	asf_msg_header_pack_tag(d, a);
	asf_msg_header_pack_reserved(d, a);
	asf_msg_header_pack_data_length(d, a);
}

void asf_header_unpack(uint8_t *d, struct asf_header *a)
{
	asf_msg_header_unpack_iana(d, a);
	asf_msg_header_unpack_type(d, a);
	asf_msg_header_unpack_tag(d, a);
	asf_msg_header_unpack_reserved(d, a);
	asf_msg_header_unpack_data_length(d, a);
}

void rmcp_header_print(struct rmcp_header *r)
{
	printf("rmcp version:   %u\n", rmcp_msg_header_get_version(r));
	printf("rmcp sequence:  %u\n", rmcp_msg_header_get_sequence(r));
	printf("rmcp reserved:  %u\n", rmcp_msg_header_get_reserved(r));
	printf("rmcp class ack  %u\n", rmcp_msg_header_get_class_ack(r));
	printf("rmcp class tag: %u\n", rmcp_msg_header_get_class_tag(r));
}

void asf_header_print(struct asf_header *a)
{
	printf("asf iana:       %u\n", asf_msg_header_get_iana(a));
	printf("asf type:       %Xh\n", asf_msg_header_get_type(a));
	printf("asf tag:        %u\n", asf_msg_header_get_tag(a));
	printf("asf reserved:   %u\n", asf_msg_header_get_reserved(a));
	printf("asf length:     %u\n", asf_msg_header_get_length(a));
}

void ping_print(uint8_t *d)
{
	struct rmcp_header r;
	struct asf_header a;

	asf_header_unpack(d, &a);
	rmcp_header_unpack(d, &r);

	rmcp_header_print(&r);
	asf_header_print(&a);
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
	s.sin_addr.s_addr = inet_addr("ip.add.re.ss");
	l = sizeof(s);

	if ((connect(fd, (struct sockaddr *)&s, l) < 0) || errno)
		goto out;

	if ((sendto(fd, d, ASF_MSG_PING_LEN, 0, (struct sockaddr *)NULL, l) < 0) || errno)
		goto out;

	if ((recvfrom(fd, r, ASF_MSG_PING_LEN, 0, (struct sockaddr *)NULL, NULL) < 0) || errno)
		goto out;

	return;

out:
	fprintf(stderr, "%s: (%d) %s\n", __func__, errno, strerror(errno));
	exit(1);
}

void req()
{
	struct rmcp_header r;
	struct asf_header a;

	struct rmcp_header rs;
	struct asf_header as;
	uint8_t d[ASF_MSG_PING_LEN];
	uint8_t ds[LONGEST];
	memset(d, '\0', ASF_MSG_PING_LEN);
	memset(ds, '\0', LONGEST);

	rmcp_header_set(&r);
	asf_header_set(&a);

	printf("SENT\n");
	rmcp_header_print(&r);
	asf_header_print(&a);

	rmcp_header_pack(d, &r);
	asf_header_pack(d, &a);

	udp(d, ds);

	rmcp_header_unpack(ds, &rs);
	asf_header_unpack(ds, &as);

	printf("\nRECIEVED\n");
	rmcp_header_print(&rs);
	asf_header_print(&as);
}

int main(void)
{
	req();
}
