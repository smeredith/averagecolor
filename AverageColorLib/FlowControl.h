#pragma once

#define IF_FAIL_RETURN(exp) \
    do { \
            const HRESULT __hr = (exp); \
            if (FAILED(__hr)) \
            { \
                return __hr; \
            } \
    } while(0,0);

#define IF_FALSE_RETURN(exp, hresult) \
    do { \
            if (!exp) \
            { \
                return hresult; \
            } \
    } while(0,0);

#define VERIFY_PARAM(exp) \
    do { \
            if (!exp) \
            { \
                return E_INVALIDARG; \
            } \
    } while(0,0);
