export async function onRequestGet({ request, env }) {
  const cookie = request.headers.get("Cookie") || "";
  const match = cookie.match(/user=([^;]+)/);
  if (!match) return new Response("Not logged in", { status: 401 });

  return Response.json({ username: match[1] });
}
