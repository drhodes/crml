#ifndef JSLOG_CC
#define JSLOG_CC

#define JS_LOG(msg)														\
    const size_t line_number = __LINE__;								\
    size_t len = floor(line_number) + 1;								\
    len = std::string(msg).size() + strlen(__FILE__) + len + 5;			\
    char buffer[len];													\
    memset(buffer, 0, len);												\
    snprintf(buffer, len, "%s:%i - ", __FILE__, line_number);			\
    strncat(buffer, std::string(msg).c_str(), len - strlen(buffer));	\
    Log(npp_, buffer);


	// Log given message to javascript console.
	bool Log(NPP npp, const char* msg, ...) {
		bool rv = false;
		NPObject* window = NULL;
		if (NPERR_NO_ERROR == NPN_GetValue(npp, NPNVWindowNPObject, &window)) {
			const char buffer[] = "top.console";
			NPString console_stript = { 0 };
			console_stript.UTF8Length = strlen(buffer);
			console_stript.UTF8Characters = buffer;
			NPVariant console;
			if (NPN_Evaluate(npp, window, &console_stript, &console)) {
				if (NPVARIANT_IS_OBJECT(console)) {
					// Convert the message to NPString;
					NPVariant text;
					STRINGN_TO_NPVARIANT(msg, static_cast<uint32_t>(strlen(msg)),
										 text);
					NPVariant result;
					if (NPN_Invoke(npp, NPVARIANT_TO_OBJECT(console),
								   NPN_GetStringIdentifier("log"), &text, 1, &result)) {
						NPN_ReleaseVariantValue(&result);
						rv = true;
					}
				}
				NPN_ReleaseVariantValue(&console);
			}
		}
		return rv;
	}

#endif
