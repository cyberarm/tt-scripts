#pragma once

#include "BattleView_Entity.h"

class BattleViewHTTPClient
{
	const char *m_user_agent;
	const char *m_endpoint_path;
	const char *m_endpoint;
	const char *m_token;

	HINTERNET m_session;
	HINTERNET m_connection;
	HINTERNET m_request;
	bool m_ready;

public:
	BattleViewHTTPClient(const char *endpoint, const char *token);
	~BattleViewHTTPClient();
	bool enqueue(BattleViewEntity *entity);
	bool post(const char* json);
	bool is_ready();
};

void CALLBACK BattleViewHTTPClient_StatusCallback(HINTERNET hInternet,
																									DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);