#include "General.h"
#include "include/BattleView_HTTPClient.h"

BattleViewHTTPClient::BattleViewHTTPClient(const char *endpoint, const char *token)
{
	m_endpoint = endpoint;
	m_token = token;

	m_ready = false;
	m_user_agent = "BattleViewPlugin/0.0";

	// FIXME!
	// Validate endpoint before continuing
	Console_Output("Endpoint: %s\n", m_endpoint);

    m_session = InternetOpen(
        m_user_agent,
        INTERNET_OPEN_TYPE_PRECONFIG,
        nullptr,
        nullptr,
        INTERNET_FLAG_ASYNC
    );

    InternetSetStatusCallback(m_session, (INTERNET_STATUS_CALLBACK)BattleViewHTTPClient_StatusCallback);

    // m_connection = HttpOpenRequest(m_session, "POST", NULL, );

    // m_connection = InternetOpenUrl(
    //     m_session,
    //     m_endpoint,
    //     "",
    //     0,
    //     INTERNET_FLAG_SECURE,
    //     (LPARAM)this);
}

BattleViewHTTPClient::~BattleViewHTTPClient()
{
    //InternetCloseHandle(m_session);
}

bool BattleViewHTTPClient::enqueue(BattleViewEntity *entity)
{
	return false;
}
bool BattleViewHTTPClient::post(const char* json)
{
    // ThreadClass* thread = new ThreadClass();
    Console_Output("Attempting InternetOpenURL\n");

    //InternetCloseHandle(m_connection);

    return true;
}

bool BattleViewHTTPClient::is_ready()
{
	return true;//m_session != nullptr;
}

void CALLBACK BattleViewHTTPClient_StatusCallback(HINTERNET internet, DWORD context, DWORD internet_status,
												  LPVOID status_information, DWORD status_information_length)
{
    //if (true || BATTLEVIEW_DEBUG_HTTPCLIENT) {
	    Console_Output("STATUS: %i\n", internet_status);
	    Console_Output("IS_READY: %i\n", ((BattleViewHTTPClient *)context)->is_ready());
    //}
}