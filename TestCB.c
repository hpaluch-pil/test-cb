// TestCB.c - simple Test how to use Pickering ClientBridge/C++ library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Picmlx.h>
#include <Piplx.h>

static DWORD LastErr = NO_ERROR;
static char ErrorBuf[1024] = { 0 };

static void AppendAndPrintPicmlxError() {
	snprintf(ErrorBuf + strlen(ErrorBuf),
			sizeof(ErrorBuf) - strlen(ErrorBuf) - 1, ": [err=%u] ", LastErr);
	PICMLX_ErrorCodeToMessage(LastErr, ErrorBuf + strlen(ErrorBuf),
			sizeof(ErrorBuf) - strlen(ErrorBuf) - 1);
	fprintf(stderr, "%s\n", ErrorBuf);
}

static void AppendAndPrintPiplxError() {
	snprintf(ErrorBuf + strlen(ErrorBuf),
			sizeof(ErrorBuf) - strlen(ErrorBuf) - 1, ": [err=%u] ", LastErr);
	PIPLX_ErrorCodeToMessage(LastErr, ErrorBuf + strlen(ErrorBuf),
			sizeof(ErrorBuf) - strlen(ErrorBuf) - 1);
	fprintf(stderr, "%s\n", ErrorBuf);
}

static const DWORD Port = 1024;

int main(int argc, char **argv) {
	char CardId[1024] = { 0 };
	char *LxiIp = NULL;
	DWORD Bus = 0, Slot = 0;
	SESSION Sid = INVALID_SESSION;
	DWORD CardNum = 0;
	int ret = EXIT_FAILURE;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s LXI_IP_ADDRESS BUS SLOT\n", argv[0]);
		fprintf(stderr, "For example: %s 192.168.10.38 1 15\n", argv[0]);
		goto exit1;
	}

	LxiIp = argv[1];
	// TODO: check for wrong arguments...
	Bus = atoi(argv[2]);
	Slot = atoi(argv[3]);

	LastErr = PICMLX_Connect(0, LxiIp, Port, 10000, &Sid);
	if (LastErr != NO_ERROR) {
		snprintf(ErrorBuf, sizeof(ErrorBuf),
				"Error connecting to LXI on '%s:%u'", LxiIp, Port);
		AppendAndPrintPicmlxError();
		goto exit1;
	}
	printf("OK: Connected to '%s:%u', SESSION=%lu\n", LxiIp, Port, Sid);

	LastErr = PIPLX_OpenSpecifiedCard(Sid, Bus, Slot, &CardNum);
	if (LastErr != NO_ERROR) {
		snprintf(ErrorBuf, sizeof(ErrorBuf),
				"Error on PIPLX_OpenSpecifiedCard(Sid=%ld, Bus=%u, Slot=%u, &CardNum=%p)",
				Sid, Bus, Slot, &CardNum);
		AppendAndPrintPiplxError();
		goto exit2;
	}
	printf("OK: OpenSpecifiedCard at Bus=%u, Slot=%u. CardNum=%u\n", Bus, Slot,
			CardNum);

	LastErr = PIPLX_CardId(Sid, CardNum, CardId, sizeof(CardId));
	if (LastErr != NO_ERROR) {
		snprintf(ErrorBuf, sizeof(ErrorBuf),
				"Error on PIPLX_CardId(Sid=%ld, CardNum=%u, &Str=%p,StrLen=%zu)",
				Sid, CardNum, CardId, sizeof(CardId));
		AppendAndPrintPiplxError();
		goto exit3;
	}
	printf("OK: Card on Bus=%u, Slot=%u has CardId='%s'\n", Bus, Slot, CardId);

	ret = EXIT_SUCCESS;

	exit3: LastErr = PIPLX_CloseSpecifiedCard(Sid, CardNum);
	if (LastErr != NO_ERROR) {
		ret = EXIT_FAILURE;
		snprintf(ErrorBuf, sizeof(ErrorBuf),
				"Error on PIPLX_CloseSpecifiedCard(Sid=%ld, CardNum=%u)", Sid,
				CardNum);
		AppendAndPrintPiplxError();
	}
	CardNum = 0;

	exit2:
	LastErr = PICMLX_Disconnect(Sid);
	if (LastErr != NO_ERROR) {
		ret = EXIT_FAILURE;
		snprintf(ErrorBuf, sizeof(ErrorBuf),
				"Error on PICMLX_Disconnect(Sid=%ld)", Sid);
		AppendAndPrintPicmlxError();
	}
	Sid = INVALID_SESSION;

	exit1: return ret;
}

