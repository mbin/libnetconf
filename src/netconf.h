/**
 * \file netconf.h
 * \author Radek Krejci <rkrejci@cesnet.cz>
 * \brief libnetconf's general public functions and structures definitions.
 *
 * Copyright (C) 2012 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef NETCONF_H_
#define NETCONF_H_

#include <sys/types.h>

struct nc_msg;

/**
 * @brief rpc message.
 * @ingroup rpc
 */
typedef struct nc_msg nc_rpc;

/**
 * @brief reply message.
 * @ingroup reply
 */
typedef struct nc_msg nc_reply;

/**
 * @brief Event notification message.
 * @ingroup notifications
 */
typedef struct nc_msg nc_ntf;

/**
 * @ingroup session
 * @brief NETCONF capabilities structure
 */
struct nc_cpblts;

/**
 * @ingroup session
 * @brief Type representing NETCONF message-id attribute.
 *
 * It corresponds to the following typedef:
 * typedef char* nc_msgid;
 *
 * We use a macro to avoid compiler warning of 'const nc_msgid' as return type
 * of functions (because const is applied as 'char* const funct()' which is
 * meaningless).
 *
 * Yes, I know that const char* means "pointer to constant character (not
 * string)", but I want to be clear from the API, that function returns pointer
 * to something that should not be changed.
 */
#define nc_msgid char*

/**
 * @brief NETCONF session description structure
 * @ingroup session
 */
struct nc_session;

/**
 * @ingroup rpc
 * @brief NETCONF filter.
 */
struct nc_filter;

/**
 * @ingroup session
 * @brief Enumeration of the possible states of a NETCONF session.
 */
typedef enum NC_SESSION_STATUS {
	NC_SESSION_STATUS_ERROR = -1, /**< undefined status or the error return code */
	NC_SESSION_STATUS_STARTUP = 0, /**< session is setting up */
	NC_SESSION_STATUS_WORKING = 1, /**< session is established and ready to work */
	NC_SESSION_STATUS_CLOSING = 2, /**< session is being closed */
	NC_SESSION_STATUS_CLOSED = 3, /**< session was closed and could not be used for communication */
	NC_SESSION_STATUS_DUMMY = 4 /**< session is DUMMY, only holds information, does not provide connection */
} NC_SESSION_STATUS;

/**
 * @ingroup session
 * @brief Enumeration of reasonf of the NETCONF session termination as defined
 * in RFC 6470.
 */
typedef enum NC_SESSION_TERM_REASON {
	NC_SESSION_TERM_CLOSED, /**< closed by client in a normal fashion */
	NC_SESSION_TERM_KILLED, /**< session was terminated by \<kill-session\> operation */
	NC_SESSION_TERM_DROPPED, /**< transport layer connection was unexpectedly closed */
	NC_SESSION_TERM_TIMEOUT, /**< terminated because of inactivity */
	NC_SESSION_TERM_BADHELLO, /**< \<hello\> message was invalid */
	NC_SESSION_TERM_OTHER /**< terminated for some other reason */
} NC_SESSION_TERM_REASON;

/**
 * @brief Enumeration of NETCONF message types.
 * @ingroup genAPI
 */
typedef enum NC_MSG_TYPE {
	NC_MSG_UNKNOWN, /**< error state */
	NC_MSG_WOULDBLOCK, /**< waiting for another message timed out */
	NC_MSG_NONE, /**< no message at input or message was processed internally */
	NC_MSG_HELLO, /**< \<hello\> message */
	NC_MSG_RPC, /**< \<rpc\> message */
	NC_MSG_REPLY, /**< \<rpc-reply\> message */
	NC_MSG_NOTIFICATION = -5 /**< \<notification\> message */
} NC_MSG_TYPE;

/**
 * @brief Enumeration of \<rpc-reply\> types.
 * @ingroup reply
 */
typedef enum NC_REPLY_TYPE {
	NC_REPLY_UNKNOWN, /**< value describing that no rpc-reply type was detected so far */
	NC_REPLY_HELLO, /**< \<hello\> message type, same as NC_RPC_HELLO */
	NC_REPLY_OK, /**< \<ok\> rpc-reply message type */
	NC_REPLY_ERROR, /**< \<rpc-error\> rpc-reply message type */
	NC_REPLY_DATA /**< rpc-reply message containing \<data\> */
} NC_REPLY_TYPE;

/**
 * @brief Enumeration of \<rpc\> operation types.
 * @ingroup rpc
 */
typedef enum NC_RPC_TYPE {
	NC_RPC_UNKNOWN, /**< value describing that no supported operation type was detected so far */
	NC_RPC_HELLO, /**< \<hello\> message type, same as NC_REPLY_HELLO */
	NC_RPC_DATASTORE_READ, /**< \<rpc\> contains operation reading datastore */
	NC_RPC_DATASTORE_WRITE, /**< \<rpc\> contains operation modifying datastore */
	NC_RPC_SESSION /**< \<rpc\> contains operation affecting the session */
} NC_RPC_TYPE;

typedef enum NC_NOTIF_TYPE {
	NC_NTF_UNKNOWN,
	NC_NTF_BASE
} NC_NOTIF_TYPE;

/**
 * @brief Enumeration of supported \<rpc\> operations
 * @ingroup rpc
 */
typedef enum NC_OP {
	NC_OP_UNKNOWN,		/**< unknown/error value */
	NC_OP_GETCONFIG,	/**< \<get-config\> operation */
	NC_OP_GET,		/**< \<get\> operation */
	NC_OP_EDITCONFIG,	/**< \<edit-config\> operation */
	NC_OP_CLOSESESSION,	/**< \<close-session\> operation */
	NC_OP_KILLSESSION,	/**< \<kill-session\> operation */
	NC_OP_COPYCONFIG,	/**< \<copy-config\> operation */
	NC_OP_DELETECONFIG,	/**< \<delete-config\> operation */
	NC_OP_LOCK,		/**< \<lock\> operation */
	NC_OP_UNLOCK,		/**< \<unlock\> operation */
	NC_OP_COMMIT,		/**< \<commit> operation */
	NC_OP_DISCARDCHANGES,	/**< \<discard-changes> operation */
	NC_OP_CREATESUBSCRIPTION,	/**< \<create-subscription\> operation (RFC 5277) */
	NC_OP_GETSCHEMA	/**< \<get-schema> operation (RFC 6022) */
} NC_OP;

typedef enum NC_ERR_PARAM {
	/**
	 * error-type - The conceptual layer that the error occurred, accepted
	 * values include 'transport', 'rpc', 'protocol', 'application'.
	 */
	NC_ERR_PARAM_TYPE,
	/**
	 * error-tag - Contains a string identifying the error condition.
	 */
	NC_ERR_PARAM_TAG,
	/**
	 * error-severity - The error severity, accepted values are 'error' and
	 * 'warning'.
	 */
	NC_ERR_PARAM_SEVERITY,
	/**
	 * error-app-tag - Contains a string identifying the data-model-specific
	 * or implementation-specific error condition, if one exists. This
	 * element will not be present if no appropriate application error-tag
	 * can be associated with a particular error condition. If both a
	 * data-model-specific and an implementation-specific error-app-tag
	 * exist then the data-model-specific value MUST be used by the
	 * server.
	 */
	NC_ERR_PARAM_APPTAG,
	/**
	 * error-path - Contains an absolute XPath expression identifying the
	 * element path to the node that is associated with the error being
	 * reported.
	 */
	NC_ERR_PARAM_PATH,
	/**
	 * error-message - A string describing the error.
	 */
	NC_ERR_PARAM_MSG,
	/**
	 * bad-attribute in error-info - name of the attribute, contained in
	 * the 'bad-attribute', 'missing-attribute' and 'unknown-attribute' errors.
	 */
	NC_ERR_PARAM_INFO_BADATTR,
	/**
	 * bad-element in error-info - name of the element, contained in
	 * 'missing-attribute', bad-attribute', 'unknown-attribute',
	 * 'missing-element', 'bad-element', 'unknown-element' and
	 * 'unknown-namespace' errors.
	 */
	NC_ERR_PARAM_INFO_BADELEM,
	/**
	 * bad-namespace in error-info - name of an unexpected namespace,
	 * contained in the 'unknown-namespace' error.
	 */
	NC_ERR_PARAM_INFO_BADNS,
	/**
	 * session-id in error-info - session ID of the session holding the
	 * requested lock, contained in 'lock-denied' error.
	 */
	NC_ERR_PARAM_INFO_SID
} NC_ERR_PARAM;

/**
 * @brief Enumeration of the supported types of datastores defined by NETCONF
 * @ingroup store
 */
typedef enum NC_DATASTORE_TYPE {
	NC_DATASTORE_ERROR, /**< error state of functions returning the datastore type */
	NC_DATASTORE_CONFIG, /**< value describing that the datastore is set as config */
	NC_DATASTORE_URL, /**< value describing that the datastore data should be given from the URL */
	NC_DATASTORE_RUNNING, /**< base NETCONF's datastore containing the current device configuration */
	NC_DATASTORE_STARTUP, /**< separated startup datastore as defined in Distinct Startup Capability */
	NC_DATASTORE_CANDIDATE /**< separated working datastore as defined in Candidate Configuration Capability */
} NC_DATASTORE;

/**
 * @ingroup rpc
 * @brief Enumeration of supported NETCONF filter types.
 */
typedef enum NC_FILTER_TYPE {
	NC_FILTER_UNKNOWN,
	NC_FILTER_SUBTREE /**< NC_FILTER_SUBTREE */
} NC_FILTER_TYPE;

/* default operations IDs for edit-config */
typedef enum NC_EDIT_OP_TYPE {
	NC_EDIT_OP_ERROR = -1, /* for internal purposes, not defined by NETCONF */
	NC_EDIT_OP_MERGE = 1,
	NC_EDIT_OP_REPLACE = 2,
	NC_EDIT_OP_CREATE,
	NC_EDIT_OP_DELETE,
	NC_EDIT_OP_REMOVE
} NC_EDIT_OP_TYPE;

typedef enum NC_EDIT_DEFOP_TYPE {
	NC_EDIT_DEFOP_ERROR = -1, /* for internal purposes, not defined by NETCONF */
	NC_EDIT_DEFOP_NOTSET = 0, /* do not set the value, default value will be used by server */
	NC_EDIT_DEFOP_MERGE = 1,
	NC_EDIT_DEFOP_REPLACE = 2,
	NC_EDIT_DEFOP_NONE = 3
} NC_EDIT_DEFOP_TYPE;

typedef enum NC_EDIT_ERROPT_TYPE {
	NC_EDIT_ERROPT_ERROR = -1, /* for internal purposes, not defined by NETCONF */
	NC_EDIT_ERROPT_NOTSET = 0,
	NC_EDIT_ERROPT_STOP = 1,
	NC_EDIT_ERROPT_CONT = 2,
	NC_EDIT_ERROPT_ROLLBACK = 3
} NC_EDIT_ERROPT_TYPE;

typedef enum NC_EDIT_TESTOPT_TYPE {
	NC_EDIT_TESTOPT_ERROR = -1, /* for internal purposes, not defined by NETCONF */
	NC_EDIT_TESTOPT_NOTSET = 0,
	NC_EDIT_TESTOPT_TESTSET = 1, /* test-then-set */
	NC_EDIT_TESTOPT_SET = 2, /* set */
	NC_EDIT_TESTOPT_TEST = 3 /* test-only */
} NC_EDIT_TESTOPT_TYPE;

typedef enum NCWD_MODE {
	NCWD_MODE_NOTSET = 0,
	NCWD_MODE_ALL = 1,
	NCWD_MODE_TRIM = 2,
	NCWD_MODE_EXPLICIT = 4,
	NCWD_MODE_ALL_TAGGED = 8
} NCWD_MODE;

typedef enum NC_CAP_ATTR {
	NC_CAP_ATTR_WITHDEFAULTS_MODE = 1
} NC_CAP_ATTR;

/**
 * @brief Verbosity levels.
 * @ingroup genAPI
 */
typedef enum NC_VERB_LEVEL {
	NC_VERB_ERROR,  /**< Print only error messages. */
	NC_VERB_WARNING,/**< Print error and warning messages. */
	NC_VERB_VERBOSE,/**< Besides errors and warnings, print some other verbose messages. */
	NC_VERB_DEBUG   /**< Print all messages including some development debug messages. */
} NC_VERB_LEVEL;

/**
 * @brief Set libnetconf's verbosity level.
 * @param[in] level Enabled verbosity level (includes all the levels with higher priority).
 * @ingroup genAPI
 */
void nc_verbosity(NC_VERB_LEVEL level);

/**
 * @ingroup genAPI
 * @brief Initialize libnetconf for system-wide usage. This initialization is
 * shared across all the processes
 * @param[in] flags ORed flags for libnetconf initialization. Accepted values
 * include:
 *    - *NC_INIT_NOTIF* Enable Notification subsystem
 *    - *NC_INIT_NACM* Enable NETCONF Access Control subsystem
 * @return -1 on fatal error\n 0 if this is the first init after previous
 * system-wide nc_close() or system reboot\n 1 when someone else already called
 * nc_init() since last system-wide nc_close() or system reboot.
 */
int nc_init(int flags);
#define NC_INIT_NOTIF 0x00000002 /**< nc_init()'s flag to enable Notification subsystem. */
#define NC_INIT_NACM 0x00000004 /**< nc_init()'s flag to enable Acccess Control subsystem */

/**
 * @ingroup genAPI
 * @brief Set UID to detect the NACM recovery session. If this function is not
 * used, value 0 (typically root user) is used. Recovery session is used to
 * bypass NACM.
 *
 * The function takes effect only if the NC_INIT_NACM flag is used in nc_init().
 *
 * @param[in] uid User ID to be used for the recovery session.
 */
void nacm_recovery_uid(uid_t uid);

/**
 * @ingroup genAPI
 * @param[in] system Flag if close should be applied as system-wide.
 * System-wide nc_close() closes all the shared structures if no other libnetconf
 * participant is currently running. Local release of the calling instance
 * from the shared structures is done in both cases.
 * @return -1 on error\n 0 on success\n 1 in case of system-wide when there is
 * another participant using shared structures and system-wide close cannot be
 * done.
 */
int nc_close(int system);

#endif /* NETCONF_H_ */
