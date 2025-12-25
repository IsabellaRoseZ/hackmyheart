async function sha256Hex(s) {
  const buf = await crypto.subtle.digest("SHA-256", new TextEncoder().encode(s));
  return [...new Uint8Array(buf)].map(b => b.toString(16).padStart(2, "0")).join("");
}

export async function onRequestPost({ request, env }) {
  const { username, password } = await request.json();
  const hash = await sha256Hex(password || "");

  const user = await env.DB.prepare(
    "SELECT id FROM users WHERE username=? AND pass_hash=?"
  ).bind(username, hash).first();

  if (!user) {
    return new Response("Invalid credentials", { status: 401 });
  }

  return Response.json({ ok: true });
}
