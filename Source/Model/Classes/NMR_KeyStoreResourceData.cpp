#include "Model/Classes/NMR_KeyStoreResourceData.h"
#include "Common/NMR_Exception.h"
#include <memory>
#include <openssl/rand.h>

#define IV_SIZE 12
#define TAG_SIZE 16
#define KEY_SIZE 32

namespace NMR {


	nfUint64 CKeyStoreResourceData::s_nfHandleCount = 0;

	void CKeyStoreResourceData::initializeCipher() {
		m_sCipherValue.m_iv.resize(IV_SIZE, 0);
		m_sCipherValue.m_tag.resize(TAG_SIZE, 0);
		m_sCipherValue.m_key.resize(KEY_SIZE, 0);
		initializeKey();
		initializeIV();
	}

	void CKeyStoreResourceData::initializeKey() {
		int rc = RAND_bytes(m_sCipherValue.m_key.data(), (int)m_sCipherValue.m_key.size());
		if (rc != 1)
			throw CNMRException(NMR_ERROR_CALCULATIONTERMINATED);
	}

	void CKeyStoreResourceData::initializeIV() {
		int rc = RAND_bytes(m_sCipherValue.m_iv.data(), (int)m_sCipherValue.m_iv.size());
		if (rc != 1)
			throw CNMRException(NMR_ERROR_CALCULATIONTERMINATED);
	}

	CKeyStoreResourceData::CKeyStoreResourceData(std::string const & path) {
		m_sPath = path;
		m_EncryptionAlgorithm = eKeyStoreEncryptAlgorithm::Aes256Gcm;
		m_nfHandle = ++s_nfHandleCount;
		initializeCipher();
	}

	CKeyStoreResourceData::CKeyStoreResourceData(std::string const & path, eKeyStoreEncryptAlgorithm const & ea, nfBool const & compression)
	{
		m_sPath = path;
		m_EncryptionAlgorithm = ea;
		m_bCompression = compression;
		m_nfHandle = ++s_nfHandleCount;
		initializeCipher();
	}

	eKeyStoreEncryptAlgorithm CKeyStoreResourceData::getEncryptionAlgorithm() const
	{	
		return m_EncryptionAlgorithm;
	}

	nfBool CKeyStoreResourceData::getCompression() const
	{
		return m_bCompression;
	}
	NMR::PPackageModelPath CKeyStoreResourceData::getPath() const
	{
		NMR::CResourceHandler * pResourceHandler = new NMR::CResourceHandler();
		return pResourceHandler->makePackageModelPath(m_sPath);
	}

	nfUint64 CKeyStoreResourceData::getHandle() const {
		return m_nfHandle;
	}

	nfBool CKeyStoreResourceData::empty() const {
		return m_DecryptRights.empty();
	}

	CIPHERVALUE CKeyStoreResourceData::getCipherValue() const {
		return m_sCipherValue;
	}

	void CKeyStoreResourceData::setCipherValue(CIPHERVALUE const & cv) {
		m_sCipherValue = cv;
		m_bOpen = true;
	}

	bool CKeyStoreResourceData::isOpen() const {
		return m_bOpen;
	}

	void CKeyStoreResourceData::randomizeIV() {
		initializeIV();
	}

}
