export async function onRequestPost() {
  return new Response(JSON.stringify({ ok: true }), {
    headers: {
      "Content-Type": "application/json",
      "Set-Cookie": "user=; Path=/; Max-Age=0; HttpOnly; SameSite=Lax; Secure"
    }
  });
}
