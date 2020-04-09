/*++

Copyright (C) 2019 3MF Consortium

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_KeyStoreResourceData.h defines the KeyStoreResourceData Class. A ResourceData is an in memory representation of the 3MF keystore resourcedata element.

--*/

#ifndef __NMR_KEYSTORERESOURCEDATAGROUP
#define __NMR_KEYSTORERESOURCEDATAGROUP

#include <map>
#include <memory>
#include <vector>
#include "Common/NMR_Types.h"
#include "Common/NMR_SecureContentTypes.h"
#include "Model/Classes/NMR_KeyStoreAccessRight.h"
#include "Model/Classes/NMR_KeyStoreResourceData.h"
#include "Model/Classes/NMR_PackageResourceID.h"
#include "Common/NMR_UUID.h"

namespace NMR {

	class CKeyStoreResourceDataGroup {
		PUUID m_sKeyUUID;
		std::vector<PKeyStoreAccessRight> m_AccessRights;
		std::map<std::string, PKeyStoreAccessRight> m_ConsumerAccesstRight;
		std::vector<PKeyStoreResourceData> m_ResourcesData;
	protected:
		/*void initializeCipher();
		void initializeKey();
		void initializeIV();*/
	public:
		CKeyStoreResourceDataGroup(PUUID const& keyUUID);
		CKeyStoreResourceDataGroup(PUUID const& keyUUID, std::vector<PKeyStoreAccessRight> const& ar, std::vector<PKeyStoreResourceData> const& rd);
		void removeAccessRight(NMR::PKeyStoreConsumer const& consumer);
		PKeyStoreAccessRight addAccessRight(NMR::PKeyStoreConsumer const& consumer, eKeyStoreEncryptAlgorithm const& encryptAlgorithm);
		PKeyStoreAccessRight addAccessRight(PKeyStoreAccessRight const & ar);
		nfUint32 getAccessRightCount();
		PKeyStoreAccessRight getAccessRight(nfUint32 index) const;
		PKeyStoreAccessRight findAccessRightByConsumer(NMR::PKeyStoreConsumer const& consumer);
		/*PKeyStoreDecryptRight addDecryptRight(NMR::PKeyStoreConsumer const& consumer, eKeyStoreEncryptAlgorithm const& encryptAlgorithm);
		PKeyStoreDecryptRight addDecryptRight(PKeyStoreDecryptRight const & dr);
		nfUint32 getDecryptRightCount();
		PKeyStoreDecryptRight getDecryptRight(nfUint32 index) const;
		PKeyStoreDecryptRight findDecryptRightByConsumer(NMR::PKeyStoreConsumer const& consumer);
		
		eKeyStoreEncryptAlgorithm getEncryptionAlgorithm() const;
		nfBool getCompression() const;
		NMR::PPackageModelPath getPath() const;
		nfUint64 getHandle() const;

		nfBool empty() const;
		CIPHERVALUE getCipherValue() const;
		void setCipherValue(CIPHERVALUE const & cv);
		bool isOpen() const;

		void randomizeIV();*/
	};
	typedef std::shared_ptr<CKeyStoreResourceDataGroup> PKeyStoreResourceDataGroup;
}

#endif
