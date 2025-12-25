async function sha256Hex(s) {
  const buf = await crypto.subtle.digest("SHA-256", new TextEncoder().encode(s));
  return [...new Uint8Array(buf)].map(b => b.toString(16).padStart(2, "0")).join("");
}

export async function onRequestPost({ request, env }) {
  const { username, password } = await request.json();

  if (!username || !password || username.length < 3 || password.length < 8) {
    return new Response("Username must be 3+ chars, password 8+ chars", { status: 400 });
  }

  const pass_hash = await sha256Hex(password);

  try {
    await env.DB.prepare(
      "INSERT INTO users (username, pass_hash) VALUES (?, ?)"
    ).bind(username.trim(), pass_hash).run();
  } catch {
    return new Response("Username already taken", { status: 409 });
  }

  // Optional: auto-login by setting a cookie
  return new Response(JSON.stringify({ ok: true }), {
    headers: {
      "Content-Type": "application/json",
      "Set-Cookie": `user=${encodeURIComponent(username.trim())}; Path=/; HttpOnly; SameSite=Lax; Secure`
    }
  });
}
