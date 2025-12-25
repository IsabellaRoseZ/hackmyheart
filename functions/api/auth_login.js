async function sha256Hex(s) {
  const buf = await crypto.subtle.digest("SHA-256", new TextEncoder().encode(s));
  return [...new Uint8Array(buf)].map(b => b.toString(16).padStart(2, "0")).join("");
}

export async function onRequestPost({ request, env }) {
  const { username, password } = await request.json();
  const pass_hash = await sha256Hex(password || "");

  const user = await env.DB.prepare(
    "SELECT id FROM users WHERE username=? AND pass_hash=?"
  ).bind(username.trim(), pass_hash).first();

  if (!user) return new Response("Invalid username or password", { status: 401 });

  return new Response(JSON.stringify({ ok: true }), {
    headers: {
      "Content-Type": "application/json",
      "Set-Cookie": `user=${encodeURIComponent(username.trim())}; Path=/; HttpOnly; SameSite=Lax; Secure`
    }
  });
}
