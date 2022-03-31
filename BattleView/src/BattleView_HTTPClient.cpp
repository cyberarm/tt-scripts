#include "General.h"
#include "include/BattleView_HTTPClient.h"

BattleViewHTTPClient::BattleViewHTTPClient(const char* endpoint, const char* token)
{
	m_endpoint = endpoint;
	m_token = token;

	m_ready = false;
	m_user_agent = "BattleViewPlugin/0.0";
	m_endpoint_path = "/api/v1/battleview";

	Console_Output("ENDPOINT: %s, TOKEN: %s\n", endpoint, token);

	// FIXME!
	// Validate endpoint before continuing
	Console_Output("Endpoint: %s\n", m_endpoint);

	int error;

	error = WSAGetLastError();
	Console_Output("Init: WSAGetLastError: %i\n", error);

	m_session = InternetOpen(
		m_user_agent,
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		INTERNET_FLAG_ASYNC
	);

	InternetSetStatusCallback(m_session, (INTERNET_STATUS_CALLBACK) BattleViewHTTPClient_StatusCallback);

	error = WSAGetLastError();
	Console_Output("Session: WSAGetLastError: %i\n", error);

	// TODO: Check status of m_session
	if (!m_session)
		Console_Output("FAILED FAILED SESSION\n");

	m_connection = InternetOpenUrl(
		m_session,
		m_endpoint,
		NULL,
		0,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE,
		(LPARAM)this
	);

	error = WSAGetLastError();
	Console_Output("Connection: WSAGetLastError: %i\n", error);

	// TODO: Check status of m_connection?
	if (!m_connection)
		Console_Output("FAILED FAILED CONNECTION\n");

	m_response = HttpOpenRequest(
		m_connection,
		"POST",
		m_endpoint_path,
		"HTTP/1.1",
		NULL,
		NULL,
		INTERNET_FLAG_NO_CACHE_WRITE,
		0
	);

	error = WSAGetLastError();
	Console_Output("Response: WSAGetLastError: %i\n", error);

	// COMMENT
	if (!m_response)
		Console_Output("FAILED FAILED RESPONSE\n");
}

BattleViewHTTPClient::~BattleViewHTTPClient()
{
}

bool BattleViewHTTPClient::enqueue(BattleViewEntity* entity)
{
	return false;
}
bool BattleViewHTTPClient::post()
{
	int error;

	error = WSAGetLastError();
	Console_Output("Pre-Send: WSAGetLastError: %i\n", error);

	HttpSendRequest(
		m_response,
		"TODO_HEADERS",
		1024,
		"TODO_BODY",
		1024
	);

	// if (true) {
		// TODO: Get response?
	// }

	error = WSAGetLastError();
	Console_Output("Post-Send: WSAGetLastError: %i\n", error);

	return true;
}

bool BattleViewHTTPClient::is_ready()
{
	return m_ready;
}

void CALLBACK BattleViewHTTPClient_StatusCallback(HINTERNET internet, DWORD context, DWORD internet_status,
	                                              LPVOID status_information, DWORD status_information_length) {

	Console_Output("STATUS: %i\n", internet_status);
}