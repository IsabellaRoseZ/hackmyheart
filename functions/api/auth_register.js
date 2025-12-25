async function sha256Hex(s) {
  const buf = await crypto.subtle.digest("SHA-256", new TextEncoder().encode(s));
  return [...new Uint8Array(buf)].map(b => b.toString(16).padStart(2, "0")).join("");
}

export async function onRequestPost({ request, env }) {
  const { username, password } = await request.json();

  if (!username || !password || password.length < 8) {
    return new Response("Invalid input", { status: 400 });
  }

  const hash = await sha256Hex(password);

  try {
    await env.DB.prepare(
      "INSERT INTO users (username, pass_hash) VALUES (?, ?)"
    ).bind(username, hash).run();
  } catch {
    return new Response("Username taken", { status: 409 });
  }

  return Response.json({ ok: true });
}
