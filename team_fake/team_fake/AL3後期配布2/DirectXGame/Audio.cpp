#include "Audio.h"

#include <Windows.h>
#include<stdio.h>
#include <cassert>
#include "Vector2.h"


void Audio::initialize()
{
	HRESULT hr;

	//XAudioの初期化
	hr = XAudio2Create(&pXAudio2, flags);

	//マスターボイス
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (pMasteringVoice == nullptr)
	{
		wprintf(L"マスターボイスがnullptrだよ");
	}
}

void Audio::PlayWave(float volume)
{
	HRESULT hr;

	//サウンドの再生
	WAVEFORMATEX wfex{};
	//波形フォーマット設定
	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	//波形フォーマットを元にSocrceVoiceの生成
	hr = pXAudio2->CreateSourceVoice(&pSourcVoice, &wfex, 0, 2.0f, &voiceCallback);
	if FAILED(hr)
	{
		delete[] pBuffer;
		return;
	}

	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)pBuffer;
	buf.pContext = pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	if (data.size >= 0)
	{
		buf.AudioBytes = data.size;
	}
	else if (data.size < 0)
	{
		buf.AudioBytes = -data.size;
	}

	//波形データの再生
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
//	//サウンドの再生
//	WAVEFORMATEX wfex{};
//	//波形フォーマット設定
//	memcpy(&wfex, &format.fmt, sizeof(format.fmt));
//	wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;
//
//	//波形フォーマットを元にSocrceVoiceの生成
//	IXAudio2SourceVoice* pSourcVoice = nullptr;
//	hr = pXAudio2->CreateSourceVoice(&pSourcVoice, &wfex);
//	if FAILED(hr)
//	{
//		delete[] pBuffer;
//		return;
//	}
//
//	//再生する波形データの設定
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
//	//波形データの再生
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

void Audio::LoadWave(const wchar_t* filename)
{
	FileOpen(filename);

	LoadWavFile();
}

void Audio::FileOpen(const wchar_t* filename)
{
	file.open(filename, std::ios_base::binary);
	if (file.fail())
	{
		assert(0);
	}
}

void Audio::LoadWavFile()
{
	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		assert(0);
	}

	//Formatチャンクの読み込み
	file.read((char*)&format, sizeof(format));

	//Dataチャンクの読み込み
	file.read((char*)&data, sizeof(data));

	if (data.size >= 0)
	{
		//Dataチャンクのデータ部(波形データ)の読み込み
		pBuffer = new char[data.size];
		file.read(pBuffer, data.size);
	}

	else if (data.size < 0)
	{
		//Dataチャンクのデータ部(波形データ)の読み込み
		pBuffer = new char[-data.size];
		file.read(pBuffer, -data.size);
	}

	//waveファイルを閉じる
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
	//再生が終わったか確認
	XAUDIO2_VOICE_STATE state;
	if (pSourcVoice == NULL)
	{
		return false;
	}
	else
	{
		pSourcVoice->GetState(&state);//ソースボイスの状況を取得
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
