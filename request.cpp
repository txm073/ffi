#include <prsht.h>
#include <cryptuiapi.h>
#include <string.h>
#include <cstringt>


HCERTSTORE        m_hMyStore;
PCCERT_CONTEXT    m_pHSCertContext;


int main() {
    // Open the 'MY' certificate store to be presented to the user
    if(!(m_hMyStore = CertOpenStore(
        CERT_STORE_PROV_SYSTEM,
        0,
        NULL,
        CERT_SYSTEM_STORE_CURRENT_USER,
        L"MY")))
    {
        // Let the user know we could not open the store.
        CString tMsg, tTitle;
        GetErrorMessage(GetLastError(), &tMsg);
        MessageBox((LPCTSTR) tMsg, 
                (LPCTSTR) tTitle.LoadString(IDS_TITLEFAILED), 
                MB_ICONEXCLAMATION);
        return FALSE;
    } else {
        // If we get to this stage, the certificate store
        // was opened successfully.
        // Display a selection of certificates to choose from.
        m_pHSCertContext = CryptUIDlgSelectCertificateFromStore(
            m_hMyStore,
            NULL,
            NULL,
            NULL,
            CRYPTUI_SELECT_EXPIRATION_COLUMN | 
            CRYPTUI_SELECT_LOCATION_COLUMN |
            CRYPTUI_SELECT_FRIENDLYNAME_COLUMN |
            CRYPTUI_SELECT_INTENDEDUSE_COLUMN ,
            0,
            NULL);
    }

    //Show an error if a certificate is not seleted.
    if (!m_pHSCertContext) {
        CString tMsg, tTitle;
        MessageBox((LPCTSTR) tMsg.LoadString(IDS_ERR1), 
                (LPCTSTR) tTitle.LoadString(IDS_ERRT1), 
                MB_ICONEXCLAMATION);
        return FALSE;
    }
}