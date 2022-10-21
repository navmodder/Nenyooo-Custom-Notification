
		void DrawNativeNotificationSetup(char* str, std::uint8_t animation, std::uint8_t afteranimation);
		void DrawNativeNotification(string str, int timer);
		void DrawNativeNotification_Starter();
		float m_DrawBaseNotificationY{};
		float m_NotificationHeight = 0.03f;
		
		void UIManager::DrawNativeNotificationSetup(char* str, std::uint8_t animation, std::uint8_t afteranimation)
		{


			m_DrawBaseNotificationY += m_DescriptionHeightPadding;


			float RectWidth = m_Width * 1.0;
			float RectHeight = m_NotificationHeight * 1;

			float posX = 0.9f;

			float posY = m_DrawBaseNotificationY + (m_FooterHeight / 2.f) + 0.12;
			DrawSprite(
				"shared",
				"info_icon_32",
				posX - 0.09,
				posY - 0.004,
				0.015,
				0.025,
				{ 255,255,255,afteranimation },
				0);
				//draw line
				DrawRect(
					posX,
					posY - 0.0165,
					m_Width,
					0.003, {
					m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b,afteranimation });
			//draw background
			DrawRect(
				posX,
				posY,
				RectWidth,
				RectHeight,
				{ m_OptionUnselectedBackgroundColor.r,m_OptionUnselectedBackgroundColor.g,m_OptionUnselectedBackgroundColor.b,animation });
			int length = strlen(str);
			if (length > 61)
			{
				if (isFullscreen)
					DrawRect(
						posX,
						posY + 0.0185,
						RectWidth,
						RectHeight / 4.1,
						{ m_OptionUnselectedBackgroundColor.r,m_OptionUnselectedBackgroundColor.g,m_OptionUnselectedBackgroundColor.b,animation });
				else
					DrawRect(
						posX,
						posY + 0.0195,
						RectWidth,
						RectHeight / 4.1,
						{ m_OptionUnselectedBackgroundColor.r,m_OptionUnselectedBackgroundColor.g,m_OptionUnselectedBackgroundColor.b,animation });

			}


			DrawLeftText(
				str,
				posX - 0.08,
				posY - 0.015,
				m_DescriptionTextSize,
				m_DescriptionTextSize,
				Font::ChaletComprimeCologne,
				{ m_DescriptionTextColor.r,m_DescriptionTextColor.g,m_DescriptionTextColor.b, afteranimation },
				false, false);


			m_DrawBaseNotificationY += m_NotificationHeight;
		}
#define DrawNativeNotification_MAX  10
		bool DrawNativeNotification_Starter_Bool[DrawNativeNotification_MAX] = { false };
		int DrawNativeNotification_Starter_Int[DrawNativeNotification_MAX] = { 0 };
		int DrawNativeNotification_Starter_A_Int[DrawNativeNotification_MAX] = { 0 };
		int DrawNativeNotification_Starter_A_Int_Timer[DrawNativeNotification_MAX] = { 0 };
		string DrawNativeNotification_Starter_Str[DrawNativeNotification_MAX] = { "" };
		void UIManager::DrawNativeNotification_Starter()
		{
			for (int i = 0; i < DrawNativeNotification_MAX; i++)
			{
				char* text = Features::StringToChar(DrawNativeNotification_Starter_Str[i]);
				if (DrawNativeNotification_Starter_Bool[i])
				{
					if (DrawNativeNotification_Starter_Int[i] < DrawNativeNotification_Starter_A_Int_Timer[i]) {
						DrawNativeNotification_Starter_Int[i] = DrawNativeNotification_Starter_Int[i] + 1;
						if (DrawNativeNotification_Starter_A_Int[i] < 80) {
							DrawNativeNotification_Starter_A_Int[i] = DrawNativeNotification_Starter_A_Int[i] + 5;
							DrawNativeNotificationSetup(text, DrawNativeNotification_Starter_A_Int[i], DrawNativeNotification_Starter_A_Int[i]);
						}
						else {
							DrawNativeNotificationSetup(text, 80, 255);
						}
						if (DrawNativeNotification_Starter_Int[i] == DrawNativeNotification_Starter_A_Int_Timer[i] - 1) {
							DrawNativeNotification_Starter_Bool[i] = false; DrawNativeNotification_Starter_Str[i].clear();
						}
					}

				}
			}
		}
		void UIManager::DrawNativeNotification(string str, int timer)
		{
			{
				for (int i = 0; i < DrawNativeNotification_MAX; i++)
				{
					if (DrawNativeNotification_Starter_Bool[i] == true)
					{
						if (!DrawNativeNotification_Starter_Str[i].empty()) {
							if (DrawNativeNotification_Starter_Str[i] == str)
								goto lebel;//avoid duplications
						}
					}
					else
					{

						DrawNativeNotification_Starter_Str[i] = str;
						DrawNativeNotification_Starter_Int[i] = 0;
						DrawNativeNotification_Starter_A_Int[i] = 0;
						DrawNativeNotification_Starter_A_Int_Timer[i] = timer;
						DrawNativeNotification_Starter_Bool[i] = true;
						goto lebel;
					}
				}
			lebel:
				str;//end
			}
		}
