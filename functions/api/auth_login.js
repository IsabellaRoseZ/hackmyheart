export async function onRequestPost({ request, env }) {
  const { username, password } = await request.json();

  const user = await env.DB.prepare(
    "SELECT id FROM users WHERE username=? AND pass_hash=?"
  ).bind(username, password ? password : "").first();

  if (!user) {
    return new Response("Invalid credentials", { status: 401 });
  }

  return new Response(JSON.stringify({ ok: true }), {
    headers: {
      "Set-Cookie": `user=${username}; Path=/; HttpOnly; SameSite=Lax`
    }
  });
}
