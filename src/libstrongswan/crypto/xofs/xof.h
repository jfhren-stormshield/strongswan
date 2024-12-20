/*
 * Copyright (C) 2017 Tobias Brunner
 * Copyright (C) 2016-2023 Andreas Steffen
 *
 * Copyright (C) secunet Security Networks AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup xof xof
 * @{ @ingroup crypto
 */

#ifndef XOF_H_
#define XOF_H_

typedef enum ext_out_function_t ext_out_function_t;
typedef struct xof_t xof_t;

#include <library.h>

/**
 * Extendable Output Functions.
 */
enum ext_out_function_t {
	XOF_UNDEFINED,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA1,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA224,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA256,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA384,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA512,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA3_224,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA3_256,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA3_384,
	/** RFC 8017 PKCS#1 */
	XOF_MGF1_SHA3_512,
	/** FIPS 202 */
	XOF_SHAKE_128,
	/** FIPS 202 */
	XOF_SHAKE_256,
	/** RFC 7539 ChaCha20 */
	XOF_CHACHA20,
};

/**
 * enum name for ext_out_function_t.
 */
extern enum_name_t *ext_out_function_names;

/**
 * Generic interface for Extended Output Function (XOF)
 */
struct xof_t {

	/**
	 * Return the type of the Extended Output Function
	 *
	 * @return			XOF type
	 */
	ext_out_function_t (*get_type)(xof_t *this);

	/**
	 * Generates pseudo random bytes and writes them in the buffer.
	 *
	 * @param out_len	number of output bytes requested
	 * @param buffer	pointer where the generated bytes will be written
	 * @return			TRUE if bytes generated successfully
	 */
	bool (*get_bytes)(xof_t *this, size_t out_len,
					  uint8_t *buffer) __attribute__((warn_unused_result));

	/**
	 * Generates pseudo random bytes and allocate space for them.
	 *
	 * @param out_len	number of output bytes requested
	 * @param chunk		chunk which will hold generated bytes
	 * @return			TRUE if bytes allocated and generated successfully
	 */
	bool (*allocate_bytes)(xof_t *this, size_t out_len,
						   chunk_t *chunk) __attribute__((warn_unused_result));

	/**
	 * Get the output block size
	 *
	 * @return			block size in bytes
	 */
	size_t (*get_block_size)(xof_t *this);

	/**
	 * Get the recommended minimum seed size
	 *
	 * @return			seed size in bytes
	 */
	size_t (*get_seed_size)(xof_t *this);

	/**
	 * Set the key for this xof_t object.
	 *
	 * @param seed		seed to set
	 * @return			TRUE if XOF initialized with seed successfully
	 */
	bool (*set_seed)(xof_t *this,
					 chunk_t seed) __attribute__((warn_unused_result));

	/**
	 * Destroys a xof object.
	 */
	void (*destroy)(xof_t *this);
};

/**
 * Determine an MGF1 XOF type for the given hash algorithm.
 *
 * @param alg			hash algorithm to map
 * @return				MGF1 XOF type if available, XOF_UNDEFINED otherwise
 */
ext_out_function_t xof_mgf1_from_hash_algorithm(hash_algorithm_t alg);

#endif /** XOF_H_ @}*/
