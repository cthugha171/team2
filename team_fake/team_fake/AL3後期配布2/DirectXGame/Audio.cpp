#include "Audio.h"

#include <Windows.h>
#include<stdio.h>
#include <cassert>
#include "Vector2.h"


void Audio::initialize()
{
	HRESULT hr;

	//XAudio�̏�����
	hr = XAudio2Create(&pXAudio2, flags);

	//�}�X�^�[�{�C�X
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (pMasteringVoice == nullptr)
	{
		wprintf(L"�}�X�^�[�{�C�X��nullptr����");
	}
}

void Audio::PlayWave(UINT texnumber, float volume)
{
	HRESULT hr;

	//�T�E���h�̍Đ�
	WAVEFORMATEX wfex{};
	//�g�`�t�H�[�}�b�g�ݒ�
	memcpy(&wfex, &format[texnumber].fmt, sizeof(format[texnumber].fmt));
	wfex.wBitsPerSample = format[texnumber].fmt.nBlockAlign * 8 / format[texnumber].fmt.nChannels;

	//�g�`�t�H�[�}�b�g������SocrceVoice�̐���
	hr = pXAudio2->CreateSourceVoice(&pSourcVoice, &wfex, 0, 2.0f, &voiceCallback);
	if FAILED(hr)
	{
		delete[] pBuffer;
		return;
	}

	//�Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)pBuffer;
	buf.pContext = pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	if (data[texnumber].size >= 0)
	{
		buf.AudioBytes = data[texnumber].size;
	}
	else if (data[texnumber].size < 0)
	{
		buf.AudioBytes = -data[texnumber].size;
	}

	//�g�`�f�[�^�̍Đ�
	hr = pSourcVoice->SubmitSourceBuffer(&buf);
	if FAILED(hr) {
		delete[] pBuffer;
		assert(0);
		return;
	}

	TargetVolume = volume * volume;
	pSourcVoice->SetVolume(TargetVolume);
	hr = pSourcVoice->Start();
	if FAILED(hr) {
		delete[] pBuffer;
		assert(0);
		return;
	}
}

//void Audio::PlayLoopWave(const char* filename, float volume)
//{
//	HRESULT hr;
//
//	//�T�E���h�̍Đ�
//	WAVEFORMATEX wfex{};
//	//�g�`�t�H�[�}�b�g�ݒ�
//	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
//	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;
//
//	//�g�`�t�H�[�}�b�g������SocrceVoice�̐���
//	IXAudio2SourceVoice* pSourcVoice = nullptr;
//	hr = pXAudio2->CreateSourceVoice(&pSourcVoice, &wfex);
//	if FAILED(hr)
//	{
//		delete[] pBuffer;
//		return;
//	}
//
//	//�Đ�����g�`�f�[�^�̐ݒ�
//	XAUDIO2_BUFFER buf{};
//	buf.pAudioData = (BYTE*)pBuffer;
//	buf.pContext = pBuffer;
//	buf.Flags = XAUDIO2_END_OF_STREAM;
//	if (data.size >= 0)
//	{
//		buf.AudioBytes = data.size;
//	}
//	else if (data.size < 0)
//	{
//		buf.AudioBytes = -data.size;
//	}
//	buf.LoopCount = XAUDIO2_LOOP_INFINITE;
//
//	//�g�`�f�[�^�̍Đ�
//	hr = pSourcVoice->SubmitSourceBuffer(&buf);
//	if FAILED(hr) {
//		delete[] pBuffer;
//		assert(0);
//		return;
//	}
//
//	float TargetVolume = volume * volume;
//	pSourcVoice->SetVolume(TargetVolume);
//	hr = pSourcVoice->Start();
//	if FAILED(hr) {
//		delete[] pBuffer;
//		assert(0);
//		return;
//	}
//}

void Audio::LoadWave(UINT texnumber, const wchar_t* filename)
{
	FileOpen(filename);

	LoadWavFile(texnumber);
}

void Audio::FileOpen(const wchar_t* filename)
{
	file.open(filename, std::ios_base::binary);
	if (file.fail())
	{
		assert(0);
	}
}

void Audio::LoadWavFile(UINT texnumber)
{
	//RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//�t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		assert(0);
	}

	//Format�`�����N�̓ǂݍ���
	file.read((char*)&format[texnumber], sizeof(format[texnumber]));

	//Data�`�����N�̓ǂݍ���
	file.read((char*)&data[texnumber], sizeof(data[texnumber]));

	if (data[texnumber].size >= 0)
	{
		//Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
		pBuffer = new char[data[texnumber].size];
		file.read(pBuffer, data[texnumber].size);
	}

	else if (data[texnumber].size < 0)
	{
		//Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
		pBuffer = new char[-data[texnumber].size];
		file.read(pBuffer, -data[texnumber].size);
	}

	//wave�t�@�C�������
	file.close();
}

void Audio::Discard()
{
	pSourcVoice->DestroyVoice();

	pMasteringVoice->DestroyVoice();

	pXAudio2->Release();
}

void Audio::setVolume(float volume)
{
	if (volume>0)
	{
		TargetVolume = volume * volume;
	}
	else
	{
		TargetVolume = 0;
	}
	pSourcVoice->SetVolume(TargetVolume);
}

float Audio::FadeIN(float TargetVolume, float DeltaTime)
{
	float vol = Vector2::lerp(this->TargetVolume, TargetVolume, DeltaTime);
	return vol;
}


void Audio::UpdateFade(float TargetVolume, float TargetTime, float DeltaTime)
{
	float volume = FadeIN(TargetVolume, DeltaTime / TargetTime);
	setVolume(volume);
}

bool Audio::endAudioCheck()
{
	//�Đ����I��������m�F
	XAUDIO2_VOICE_STATE state;
	if (pSourcVoice == NULL)
	{
		return false;
	}
	else
	{
		pSourcVoice->GetState(&state);//�\�[�X�{�C�X�̏󋵂��擾
		if (state.BuffersQueued <= 0)
		{
			return true;
		}
	}
	return false;
}

bool Audio::CheckAudio()
{
	XAUDIO2_VOICE_STATE state;
	if (pSourcVoice == NULL)
	{
		return false;
	}
	return true;
}
