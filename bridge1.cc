namespace scm {
	bool ScriptingBridge::SetCameraOrientation(const NPVariant* args,
											   uint32_t arg_count,
											   NPVariant* value) {
		Tumbler* tumbler = static_cast<Tumbler*>(npp_->pdata);
		if (!tumbler || arg_count != 1 || !NPVARIANT_IS_OBJECT(*args))
			return false;

		// Unpack the array object.  This is done by enumerating the identifiers on
		// the array; the identifiers are the array subscripts.

		bool success = false;
		NPIdentifier* identifier = NULL;
		uint32_t element_count = 0;

		NPObject* array_object = NPVARIANT_TO_OBJECT(*args);
		
		if (NPN_Enumerate(npp_, array_object, &identifier, &element_count)) {
			if (element_count == kQuaternionElementCount) {
				float orientation[4] = {0.0f, 0.0f, 0.0f, 1.0f};
				tumbler->GetCameraOrientation(orientation);
				
				for (uint32_t j = 0; j < element_count; ++j) {
					if (NPN_HasProperty(npp_, array_object, identifier[j])) {


						// Get each element out of the array by accessing the property whose
						// identifier is the array subscript.
						NPVariant array_elem;
						VOID_TO_NPVARIANT(array_elem);
						if (NPN_GetProperty( npp_,
											 array_object,
											 identifier[j],
											 &array_elem)) {
							// Process both integer and double values.  Other value types are
							// not handled.
							switch (array_elem.type) {
							case NPVariantType_Int32:
								orientation[j] =
									static_cast<float>(NPVARIANT_TO_INT32(array_elem));
								break;
							case NPVariantType_Double:
								orientation[j] =
									static_cast<float>(NPVARIANT_TO_DOUBLE(array_elem));
								break;
							default:
								break;
							}
						}
					}
				}
				success = tumbler->SetCameraOrientation(orientation);
				NPN_MemFree(identifier);
			}
		}

		return success;
	}
}
