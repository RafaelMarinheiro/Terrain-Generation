//Using the Oren-Nayer Model

float DiffuseLighting(	vec3 lightDirection,
						vec3 viewDirection,
						vec3 surfaceNormal,
						float roughness){

	// float cos_theta_i = dot(lightDirection, surfaceNormal);
	// float cos_theta_r = dot(viewDirection, surfaceNormal);

	float L = max(0, dot(lightDirection, surfaceNormal));
	float V = max(0, dot(viewDirection, surfaceNormal));
	float P = max(0, dot(lightDirection - surfaceNormal*L, viewDirection - surfaceNormal*V));

	float sigma2 = roughness * roughness;

	float A = 1.0 - 0.5*sigma2/(sigma2 + 0.33);
	float B = 0.45 * sigma2 / (sigma2 + 0.09);

	return max(L*(A + B*P*sqrt((1-L*L)*(1-V*V))/max(L, V))/acos(-1.0), 0.0);
	// return V;
}