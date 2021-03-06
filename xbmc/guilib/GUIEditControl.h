/*!
\file GUIEditControl.h
\brief
*/

#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "GUIButtonControl.h"
#include "utils/Stopwatch.h"
#include "utils/StringValidation.h"
#include "utils/Variant.h"

/*!
 \ingroup controls
 \brief
 */

class CGUIEditControl : public CGUIButtonControl
{
public:
  enum INPUT_TYPE {
                    INPUT_TYPE_READONLY = -1,
                    INPUT_TYPE_TEXT = 0,
                    INPUT_TYPE_NUMBER,
                    INPUT_TYPE_SECONDS,
                    INPUT_TYPE_TIME,
                    INPUT_TYPE_DATE,
                    INPUT_TYPE_IPADDRESS,
                    INPUT_TYPE_PASSWORD,
                    INPUT_TYPE_PASSWORD_MD5,
                    INPUT_TYPE_SEARCH,
                    INPUT_TYPE_FILTER,
                    INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW
                  };

  CGUIEditControl(int parentID, int controlID, float posX, float posY,
                  float width, float height, const CTextureInfo &textureFocus, const CTextureInfo &textureNoFocus,
                  const CLabelInfo& labelInfo, const std::string &text);
  explicit CGUIEditControl(const CGUIButtonControl &button);
  ~CGUIEditControl(void) override;
  CGUIEditControl *Clone() const override { return new CGUIEditControl(*this); };

  bool OnMessage(CGUIMessage &message) override;
  bool OnAction(const CAction &action) override;
  void OnClick() override;

  void SetLabel(const std::string &text) override;
  void SetLabel2(const std::string &text) override;
  void SetHint(const CGUIInfoLabel& hint);

  std::string GetLabel2() const override;

  unsigned int GetCursorPosition() const;
  void SetCursorPosition(unsigned int iPosition);

  void SetInputType(INPUT_TYPE type, CVariant heading);

  void SetTextChangeActions(const CGUIAction& textChangeActions) { m_textChangeActions = textChangeActions; };

  bool HasTextChangeActions() const { return m_textChangeActions.HasActionsMeetingCondition(); };

  virtual bool HasInvalidInput() const { return m_invalidInput; }
  virtual void SetInputValidation(StringValidation::Validator inputValidator, void *data = NULL);

protected:
  void SetFocus(bool focus) override;
  void ProcessText(unsigned int currentTime) override;
  void RenderText() override;
  CGUILabel::COLOR GetTextColor() const override;
  std::wstring GetDisplayedText() const;
  std::string GetDescriptionByIndex(int index) const override;
  bool SetStyledText(const std::wstring &text);
  void RecalcLabelPosition();
  void ValidateCursor();
  void UpdateText(bool sendUpdate = true);
  void OnPasteClipboard();
  void OnSMSCharacter(unsigned int key);
  void DefaultConstructor();  

  virtual bool ValidateInput(const std::wstring &data) const;
  void ValidateInput();

  /*! \brief Clear out the current text input if it's an MD5 password.
   \return true if the password is cleared, false otherwise.
   */
  bool ClearMD5();
  
  std::wstring m_text2;
  std::string  m_text;
  CGUIInfoLabel m_hintInfo;
  float m_textOffset;
  float m_textWidth;
  CRect m_clipRect; ///< clipping rect for the second label

  static const int spaceWidth = 5;

  unsigned int m_cursorPos;
  unsigned int m_cursorBlink;

  std::string m_inputHeading;
  INPUT_TYPE m_inputType;
  bool m_isMD5;

  CGUIAction m_textChangeActions;

  bool m_invalidInput;
  StringValidation::Validator m_inputValidator;
  void *m_inputValidatorData;

  unsigned int m_smsKeyIndex;
  unsigned int m_smsLastKey;
  CStopWatch   m_smsTimer;

  std::wstring m_edit;
  int          m_editOffset;
  int          m_editLength;

  static const char*        smsLetters[10];
  static const unsigned int smsDelay;
};
