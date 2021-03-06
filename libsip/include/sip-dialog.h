#ifndef _sip_dialog_h_
#define _sip_dialog_h_

#include "sip-header.h"
#include "cstring.h"
#include "list.h"
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

enum {
	DIALOG_ERALY = 0,
	DIALOG_CONFIRMED,
};

struct sip_agent_t;
struct sip_message_t;
struct sip_dialog_t
{
	int state; // DIALOG_ERALY/DIALOG_CONFIRMED

	char callid[128];
	struct 
	{
		uint32_t id; // local/remote sequence number
		struct sip_contact_t uri; // local/remote URI(From/To Field)
		//char tag[128]; //local/remote tag
		//char nickname[128]; //local/remote nickname
		//struct sip_uri_t uri; // local/remote URI(From/To Field)
	} local, remote;
	struct sip_uri_t target; //remote target(the URI from the Contact header field of the request)
	int secure; // bool

	// route set(the list of URIs in the Record-Route header field from the request)
	struct sip_uris_t routers;

	// internal use only
	void* session; // user-defined session
	struct list_head link;
	char* ptr;
	int32_t ref;
};

struct sip_dialog_t* sip_dialog_create(const struct sip_message_t* msg);

int sip_dialog_setremotetag(struct sip_dialog_t* dialog, const struct cstring_t* tag);

// dialog management
int sip_dialog_add(struct sip_agent_t* sip, struct sip_dialog_t* dialog);
int sip_dialog_remove(struct sip_agent_t* sip, struct sip_dialog_t* dialog);
struct sip_dialog_t* sip_dialog_find(struct sip_agent_t* sip, const struct cstring_t* callid, const struct cstring_t* local, const struct cstring_t* remote);

#if defined(__cplusplus)
}
#endif
#endif /* !_sip_dialog_h_ */
